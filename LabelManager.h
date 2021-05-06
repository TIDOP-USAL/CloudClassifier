#pragma once

#include <iostream>
#include <vector>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Classification.h>

typedef CGAL::Classification::Label_set LabelSet;
typedef CGAL::Classification::Label_handle LabelHandle;
typedef CGAL::Color Color;

struct Label {
	std::string text;
	LabelHandle handle;
	Color color;

	Label(const std::string& _text, LabelHandle& _handle, const Color& _color)
		: text(_text), handle(_handle), color(_color) {
	}
	Label() = default;
	~Label() = default;
};

class LabelManager {
private:
	LabelSet labelSet;
	std::vector<Label> labels;
public:
	LabelManager() = default;
	~LabelManager() = default;
public:
	void createLabel(const std::string& text, const Color& color);
	Label& getLabel(const std::string& text);
	Label& getLabel(unsigned int index);
public:
	inline LabelSet& getLabelSet() {
		return labelSet;
	}

	inline std::vector<Label>& getLabels() {
		return labels;
	}
};