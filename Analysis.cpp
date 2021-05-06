#include "Analysis.h"

Analysis::Analysis(const Input& _input, float _gridResolution, unsigned int _numberOfNeighbors) 
	: input(_input), gridResolution(_gridResolution), numberOfNeighbors(_numberOfNeighbors) {

	if (!input.getPoints().empty()) {
		boundingBox = CGAL::bounding_box(input.getPoints().begin(), input.getPoints().end());
		grid = PlanimetricGrid(input.getPoints(), Pmap(), boundingBox, gridResolution);
		neighborhood = Neighborhood(input.getPoints(), Pmap());
		eigen = LocalEigenAnalysis::create_from_point_set(input.getPoints(), Pmap(), neighborhood.k_neighbor_query(numberOfNeighbors));
	}
}

Analysis::Analysis(const Analysis& analysis) 
	: input(analysis.input), gridResolution(analysis.gridResolution), numberOfNeighbors(analysis.numberOfNeighbors),
	boundingBox(analysis.boundingBox), neighborhood(analysis.neighborhood), eigen(analysis.eigen) {
	grid = analysis.grid; // If it's not working, use grid = PlanimetricGrid(input.getPoints(), Pmap(), boundingBox, gridResolution); instead
}