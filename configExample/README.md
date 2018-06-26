# Generation Code
```C++
bool ConfigManager::test()
{
	int n = 4;
	Config config, config1;
	config.nFilters = n;
	FilterSlicer *fslicer = new FilterSlicer();
	FilterFlip *fflip = new FilterFlip();
	FilterAuto *fauto = new FilterAuto();
	FilterColor *fcolor = new FilterColor();

	std::vector<Geometry::Point> poly;
	int size_poly = 3;
	poly = std::vector<Geometry::Point>(size_poly);
	for(int i=0;i<size_poly;++i)
	{
		poly[i].x = 1.*rand()/rand();
		poly[i].y = 1.*rand()/rand();
	}

	fslicer->poly = poly;
	fflip->isLR = true;
	fcolor->r = 4;
	fcolor->g = 2;
	fcolor->b = 0;
	fcolor->a = 233;

	config.filters = new Filter*[n];
	config.filters[0] = fslicer;
	config.filters[1] = fflip;
	config.filters[2] = fcolor;
	config.filters[3] = fauto;

	long long id = (long long)new int();

	storeConfig(0,config);
	config1 = loadConfig(0);
	storeConfig(1,config1);


}
```
