# SlicerCore
A SlicerCore of Slicer for Weston with Wayland.

# To-do

* Do Unit test.
* Reduce times of reading config files.
* Clear the folder when starting.

# API

## Use Core

You can find this in library.h

```C++
void* slicer_connect(int64_t id, void* data, uint width, uint height);
```

To initialize this core, you should use:
```C++
slicer_connect(-1, NULL, 0, 0);
```

## Render API


You can find this in FilterRender.h

```C++
class FilterRender {
private:
	static void* doFlip(void *data, uint width, uint height, bool isLR);
	static void* doSlice(void *data, uint width, uint height, std::vector<Point>);
	static void* doColor(void *data, uint width, uint height, u_int8_t r, u_int8_t g, u_int8_t b ,u_int8_t a);
	static void* doAuto(void *data, uint width, uint height);
};
```

## Format of config files

You can find this in configManager.h

```C++
/*
 * config files: ~/.slicer/<id>
 *
 * ======================
 * format of config files
 * ======================
 *
 *      @uint n:number of filters
 *
 *      [filters]*n
 *
 * [one filter]:
 *
 *      @int8_t type: 0-flip 1-slice 2-color 3-auto
 *
 *      [when type=0]
 *
 *          @bool isLR: is Left-Right flip or not
 *
 *      [when type=1]
 *
 *          @u_int32_t nn: number of points of the polygon
 *
 *          [points]*nn
 *
 *          [one point]:
 *
 *              @double x
 *              @double y
 *
 *      [when type=2]
 *
 *          @u_int8_t r     : Red(0~255)
 *          @u_int8_t g     : Green(0~255)
 *          @u_int8_t b     : Blue(0~255)
 *          @u_int8_t alpha : Opacity(0~255)
 *
 *      [when type=3]
 *
 *          (nothing...)
 *
 */
 ```
