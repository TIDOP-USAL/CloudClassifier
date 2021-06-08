#include "LabelManager.h"

void LabelManager::createLabel(const std::string& text, const Color& color) {
	bool exists = false;
	for (Label& label : labels) {
		if (label.text == text)
			exists = true;
	}
	if (!exists) {
		LabelHandle handle = labelSet.add(text.c_str(), color);
		Label label(text, std::move(handle), color);
		labels.push_back(std::move(label));
	}
}

Label& LabelManager::getLabel(const std::string& text) {
	Label label;
	for (Label& l : labels) {
		if (l.text == text)
			return l;
	}
	return label;
}

Label& LabelManager::getLabel(unsigned int index) {
	Label label;
	if (index < labels.size())
		return labels[index];
	return label;
}