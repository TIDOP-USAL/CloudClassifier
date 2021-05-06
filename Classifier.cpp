#include "Classifier.h"

#include <CGAL/IO/write_ply_points.h>

Classifier::Classifier(FeatureManager& _featureManager)
	: featureManager(std::move(_featureManager)) {
	labelIndices = std::vector<int>(getInput().getPoints().size(), -1);
}

void Classifier::classify(const ClassificationType& classificationType) {

	CGALclassifier classifier(getLabelManager().getLabelSet(), featureManager.getFeatureSet());

	for (WeightGroup& w : weights)
		classifier.set_weight(w.feature, w.weight);

	for (EffectGroup& e : effects)
		classifier.set_effect(e.label, e.feature, e.effect);

	switch (classificationType) {
	case ClassificationType::RAW:
		CGAL::Classification::classify<CGAL::Parallel_if_available_tag>(getInput().getPoints(), getLabelManager().getLabelSet(), classifier, labelIndices);
		break;
	case ClassificationType::LOCAL_SMOOTHING:
		CGAL::Classification::classify_with_local_smoothing<CGAL::Parallel_if_available_tag>(getInput().getPoints(), Pmap(), getLabelManager().getLabelSet(),
			classifier, getAnalysis().getNeighborhood().sphere_neighbor_query(featureManager.getRadiusNeighbors()), labelIndices);
		break;
	case ClassificationType::GRAPHCUT:
		CGAL::Classification::classify_with_graphcut<CGAL::Parallel_if_available_tag>(getInput().getPoints(), Pmap(), getLabelManager().getLabelSet(), classifier,
			getAnalysis().getNeighborhood().k_neighbor_query(12), 0.2f, 4, labelIndices);
		break;
	}
}

void Classifier::save(const std::string& filePath) {

	std::vector<unsigned char> red, green, blue;
	red.reserve(getInput().getPoints().size());
	green.reserve(getInput().getPoints().size());
	blue.reserve(getInput().getPoints().size());
	for (std::size_t i = 0; i < getInput().getPoints().size(); ++i) {
		LabelHandle handle = getLabelManager().getLabelSet()[std::size_t(labelIndices[i])];
		unsigned r = 0, g = 0, b = 0;
		for (Label& label : featureManager.getAnalysis().getInput().getLabelManager().getLabels()) {
			if (handle == label.handle) {
				r = label.color.r();
				g = label.color.g();
				b = label.color.b();
			}
		}
		red.push_back(r);
		green.push_back(g);
		blue.push_back(b);
	}

	std::ofstream f(filePath);
	CGAL::write_ply_points_with_properties
	(f, CGAL::make_range(boost::counting_iterator<std::size_t>(0),
		boost::counting_iterator<std::size_t>(getInput().getPoints().size())),
		CGAL::make_ply_point_writer(CGAL::make_property_map(getInput().getPoints())),
		std::make_pair(CGAL::make_property_map(red), CGAL::PLY_property<unsigned char>("red")),
		std::make_pair(CGAL::make_property_map(green), CGAL::PLY_property<unsigned char>("green")),
		std::make_pair(CGAL::make_property_map(blue), CGAL::PLY_property<unsigned char>("blue")));
}

void Classifier::save() {

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

	std::string inputPath = getInput().getFilePath();
	std::vector<std::string> pathSplitted = split(inputPath, "/");
	std::vector<std::string> nameSplitted = split(pathSplitted[pathSplitted.size() - 1], ".");
	std::string filePath = "";
	for (int i = 0; i < pathSplitted.size() - 1; i++)
		filePath += pathSplitted[i] + "/";
	filePath += nameSplitted[0] + "-classified.ply";

	save(filePath);
}