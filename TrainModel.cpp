#include "TrainModel.h"

#include <QMessageBox>

#include <CGAL/property_map.h>
#include <CGAL/IO/write_ply_points.h>

#include "WProgressDialog.h"

TrainModel::TrainModel(const TrainController& _trainController)
	: trainController(_trainController), featureGenerator(nullptr), 
	classifier(nullptr), featureSet(nullptr) {
}

TrainModel::TrainModel(const TrainModel& trainModel) 
	: trainController(trainModel.trainController), featureGenerator(nullptr), 
	classifier(nullptr), featureSet(nullptr), labelMap(trainModel.labelMap),
	labelSet(trainModel.labelSet) {
	featureGenerator = trainModel.featureGenerator;
	classifier = trainModel.classifier;
	featureSet = trainModel.featureSet;
}

TrainModel::TrainModel(TrainModel&& trainModel) noexcept 
	: trainController(std::move(trainModel.trainController)), featureGenerator(nullptr), 
	classifier(nullptr), labelMap(std::move(trainModel.labelMap)), labelSet(std::move(trainModel.labelSet)) {
	featureGenerator = trainModel.featureGenerator;
	classifier = trainModel.classifier;
	featureSet = trainModel.featureSet;
}

TrainModel::~TrainModel() {
	if (featureGenerator != nullptr)
		delete featureGenerator;
	if (classifier != nullptr)
		delete classifier;
	if (featureSet != nullptr)
		delete featureSet;
}

void TrainModel::initInput() {
	std::string path = trainController.getFilePath();
	std::ifstream in(path, std::ios::binary);
	in >> pts;
	bool found = false;
	std::tie(labelMap, found) = pts.property_map<int>("label");
	if (!found) {
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText("Label property not found in input file");
		msgBox.exec();
	}
}

void TrainModel::calculateFeatures() {
	std::size_t scales = trainController.getScales();
	featureSet = new CFeatureSet();
	featureGenerator = new CFeatureGenerator(pts, pts.point_map(), scales);
	featureSet->begin_parallel_additions();
	featureGenerator->generate_point_based_features(*featureSet);
	featureSet->end_parallel_additions();
}

void TrainModel::createLabels() {
	for (LabelView* labelView : trainController.getLabelViews()) {
		QString text = labelView->getText();
		QColor color = labelView->getColor();
		CGAL::Color cgalColor(color.red(), color.blue(), color.green());
		CLabelHandle handle = labelSet.add(text.toLocal8Bit().constData(), cgalColor);
		mapLabels.insert(std::pair<LabelView*, LabelHandle>(labelView, handle));
	}
}

void TrainModel::train() {
	unsigned int tests = trainController.getNumberOfTests();
	classifier = new CGALClassifier(labelSet, *featureSet);
	classifier->train<CGAL::Parallel_if_available_tag>(pts.range(labelMap), tests);
}

void TrainModel::classify() {

	labelIndices = std::vector<int>(pts.size(), -1);

	//float radiusNeighbors = 0.1f;
	//CGAL::Classification::classify_with_local_smoothing<CGAL::Parallel_if_available_tag>
		//(pts,pts.point_map(), labelSet,
		//*classifier, featureGenerator->neighborhood().sphere_neighbor_query
		//(radiusNeighbors), labelIndices);

	Classification::classify_with_graphcut<CGAL::Parallel_if_available_tag>
		(pts, pts.point_map(), labelSet, *classifier,
			featureGenerator->neighborhood().k_neighbor_query(12),
			0.2f, 10, labelIndices);
}

void TrainModel::evaluation() {
	Classification::Evaluation evaluation(labelSet, pts.range(labelMap), labelIndices);
	for (Label_handle l : labelSet) {
		std::cerr << " * " << l->name() << ": "
			<< evaluation.precision(l) << " ; "
			<< evaluation.recall(l) << " ; "
			<< evaluation.f1_score(l) << " ; "
			<< evaluation.intersection_over_union(l) << std::endl;
	}
	std::cerr << "Accuracy = " << evaluation.accuracy() << std::endl
		<< "Mean F1 score = " << evaluation.mean_f1_score() << std::endl
		<< "Mean IoU = " << evaluation.mean_intersection_over_union() << std::endl;
	std::ofstream fconfig("config.xml");
	classifier->save_configuration(fconfig);
	fconfig.close();
}

std::string& TrainModel::getNewFilePath(const std::string& ext) {

	auto split = [&](const std::string str, const std::string& delim) {
		std::vector<std::string> tokens;
		size_t prev = 0, pos = 0;
		do {
			pos = str.find(delim, prev);
			if (pos == std::string::npos) pos = str.length();
			std::string token = str.substr(prev, pos - prev);
			if (!token.empty()) tokens.push_back(token);
			prev = pos + delim.length();
		} while (pos < str.length() && prev < str.length());
		return tokens;
	};

	std::string filePath = "";
	std::string inputPath = trainController.getFilePath();
	std::vector<std::string> pathSplitted = split(inputPath, "/");
	std::vector<std::string> nameSplitted = split(pathSplitted[pathSplitted.size() - 1], ".");
	
	for (int i = 0; i < pathSplitted.size() - 1; i++)
		filePath += pathSplitted[i] + "/";
	filePath += nameSplitted[0] + ext + "." + nameSplitted[1];
	return filePath;
}

void TrainModel::save(const std::string& filePath) {
	std::vector<unsigned char> red, green, blue;
	red.reserve(pts.size());
	green.reserve(pts.size());
	blue.reserve(pts.size());
	for (std::size_t i = 0; i < pts.size(); ++i) {
		LabelHandle handle = labelSet[std::size_t(labelIndices[i])];
		unsigned r = 0, g = 0, b = 0;
		for (LabelView* labelView : trainController.getLabelViews()) {
			LabelHandle labelHandle = mapLabels[labelView];
			if (labelHandle == handle) {
				QColor color = labelView->getColor();
				r = color.red();
				g = color.green();
				b = color.blue();
			}
		}

		red.push_back(r);
		green.push_back(g);
		blue.push_back(b);
	}

	std::ofstream f(filePath);

	std::vector<CPoint> points;
	Point_set::Point_range pointRange = pts.points();
	for (auto& p : pointRange)
		points.push_back(CPoint(p.x(), p.y(), p.z()));


	CGAL::write_ply_points_with_properties
	(f, CGAL::make_range(boost::counting_iterator<std::size_t>(0),
		boost::counting_iterator<std::size_t>(pts.size())),
		CGAL::make_ply_point_writer(CGAL::make_property_map(points)),
		std::make_pair(CGAL::make_property_map(red), CGAL::PLY_property<unsigned char>("red")),
		std::make_pair(CGAL::make_property_map(green), CGAL::PLY_property<unsigned char>("green")),
		std::make_pair(CGAL::make_property_map(blue), CGAL::PLY_property<unsigned char>("blue")));
}

void TrainModel::save() {
	save(getNewFilePath("-classified"));
}

void TrainModel::run() {

	unsigned int progress = 0, maxProgress = 7;
	WProgressDialog progressDialog("Train", "Loading input...", 0, maxProgress);

	#define PROGRESS(S, F, ...) progressDialog.setLabel(std::string(S)); F(__VA_ARGS__); progressDialog.setValue(++progress)

	PROGRESS("Loading input..", initInput);
	PROGRESS("Calculating features...", calculateFeatures);
	PROGRESS("Creating labels...", createLabels);
	PROGRESS("Training...", train);
	PROGRESS("Classifying...", classify);
	PROGRESS("Evaluation...", evaluation);
	PROGRESS("Saving", save);
}