//
// Created by timemachine on 18-6-26.
//

#include "FilterRender.h"
#include "filter.h"

void* FilterRender::render(void *data, uint width, uint height, Config *config) {
	if(config == NULL) return data;
	int n = config->nFilters;
	for(int i=0;i<n;++i)
	{
		switch (config->filters[i]->type())
		{
			case 0:
			{
				FilterFlip *f = (FilterFlip*)config->filters[i];
				data = FilterRender::doFlip(data, width, height, f->isLR);
				break;
			}
			case 1:
			{
				FilterSlicer *f = (FilterSlicer*)config->filters[i];
				data = FilterRender::doSlice(data, width, height, f->poly);
				break;
			}
			case 2:
			{
				FilterColor *f = (FilterColor*)config->filters[i];
				data = FilterRender::doColor(data, width, height, f->r, f->g, f->b, f->a);
				break;
			}

		}

	}
	return data;
}

void* FilterRender::doFlip(void *data, uint width, uint height, bool isLR) {

}

void* FilterRender::doSlice(void *data, uint width, uint height, std::vector<Point>) {

}

void* FilterRender::doColor(void *data, uint width, uint height, double r, double g, double b, double a) {

}
