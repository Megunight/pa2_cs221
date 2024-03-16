/**
 * @file        filler.cpp
 * @description Implementation of functions in the filler namespace.
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

/**
 * Performs a flood fill using breadth first search.
 *
 * @param config FillerConfig struct to setup the fill
 * @return animation object illustrating progression of flood fill algorithm
 */
animation filler::FillBFS(FillerConfig& config) {
	// complete your implementation below
	// You should replace the following line with a
	// correct call to fill.
    return Fill<Queue>(config);
}

/**
 * Performs a flood fill using depth first search.
 *
 * @param  config - FillerConfig struct to setup the fill
 * @return animation object illustrating progression of flood fill algorithm
 */
animation filler::FillDFS(FillerConfig& config) {
	// complete your implementation below
	// You should replace the following line with a
	// correct call to fill.
	return Fill<Stack>(config);
}

/**
 * Run a flood fill on an image starting at the seed point
 *
 * @param config FillerConfig struct with data for flood fill of image
 * @return animation object illustrating progression of flood fill algorithm
 */
template <template <class T> class OrderingStructure> animation filler::Fill(FillerConfig& config)
{
	/**
	 * You need to implement this function!
	 *
	 * This is the basic description of a flood-fill algorithm: Every fill
	 * algorithm requires an ordering structure, which is passed to this
	 * function via its template parameter. For a breadth-first-search
	 * fill, that structure is a Queue, for a depth-first-search, that
	 * structure is a Stack. To begin the algorithm, you simply place the
	 * given point in the ordering structure, marking it processed
	 * (the way you mark it is a design decision you'll make yourself).
	 * We have a choice to either change the color, if appropriate, when we
	 * add the point to the OS, or when we take it off. In our test cases,
	 * we have assumed that you will change the color when a point is removed
	 * from the structure.
	 * Until the structure is empty, you do the following:
	 *
	 * 1.     Remove a point from the ordering structure, and then...
	 *
	 *        1.1.  add its unprocessed neighbors (up/down/left/right) whose color values are
	 *              within (or equal to) tolerance distance from the seed point,
	 *              to the ordering structure, and
	 *              mark them as processed.
	 *        1.2.  if it is an appropriate frame, send the current PNG to the
	 *              animation (as described below).
	 *
	 * 2.     When implementing your breadth-first-search and
	 *        depth-first-search fills, you will need to explore neighboring
	 *        pixels (up/down/left/right) in some order.
	 *
	 *        While the order in which you examine neighbors does not matter
	 *        for a proper fill, you must use the same order as we do for
	 *        your animations to come out like ours! The order you should put
	 *        neighboring pixels **ONTO** the queue or stack is as follows:
	 *        2.1. northern neighbour (up)
	 *        2.2. eastern neighbour (right)
	 *        2.3. southern neighbour (down)
	 *        2.4. western neighbour (left)
	 * 
	 *        If you process the neighbours in a different order, your fill may
	 *        still work correctly, but your animations will be different
	 *        from the grading scripts!
	 *
	 * 3.     For every k pixels filled, **starting at the kth pixel**, you
	 *        must add a frame to the animation, where k = frameFreq.
	 *
	 *        For example, if frameFreq is 4, then after the 4th pixel has
	 *        been filled you should add a frame to the animation, then again
	 *        after the 8th pixel, etc.  You must only add frames for the
	 *        number of pixels that have been filled, not the number that
	 *        have been checked. So if frameFreq is set to 1, a pixel should
	 *        be filled every frame.
	 *
	 * 4.     Finally, as you leave the function, send one last frame to the
	 *        animation. This frame will be the final result of the fill, and
	 *        it will be the one we test against.
	 *
	 */
	int framecount = 0;
	animation anim;
	OrderingStructure<PixelPoint> os;
	PNG img = config.img;

	PixelPoint seedpoint = config.seedpoint;
	ColorPicker *colorPicker = config.picker;
	double tolerance = config.tolerance;
	int frameFq = config.frameFreq;
	int width = img.width();
	int height = img.height();
	RGBAPixel seedColor = *img.getPixel(seedpoint.x, seedpoint.y);
	RGBAPixel currColor;

	// Create a 2D array to track visited pixels
	bool **visited = new bool *[width];
	for (int i = 0; i < width; i++) {
		visited[i] = new bool[height]();
		for (int j = 0; j < height; j++) {
            visited[i][j] = false;
        }
	}

	// Add seed point to ordering structure and mark it as visited
	os.Add(seedpoint);
	visited[seedpoint.x][seedpoint.y] = true;

	/**
	 * Fill neighboring pixels
	 * 
	 * 2.     When implementing your breadth-first-search and
	 *        depth-first-search fills, you will need to explore neighboring
	 *        pixels (up/down/left/right) in some order.
	 *
	 *        While the order in which you examine neighbors does not matter
	 *        for a proper fill, you must use the same order as we do for
	 *        your animations to come out like ours! The order you should put
	 *        neighboring pixels **ONTO** the queue or stack is as follows:
	 *        2.1. northern neighbour (up)
	 *        2.2. eastern neighbour (right)
	 *        2.3. southern neighbour (down)
	 *        2.4. western neighbour (left)
	 * 
	 *        If you process the neighbours in a different order, your fill may
	 *        still work correctly, but your animations will be different
	 *        from the grading scripts!
	 * 
	 *  
	 */

	while (!os.IsEmpty()) {
		PixelPoint p = os.Remove();
		currColor = *img.getPixel(p.x, p.y);
		if (framecount % frameFq == 0) {
			anim.addFrame(img);
		}

		// Define the order to visit neighboring pixels
		const std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

		for (const auto &dir : directions) {
			int nx = p.x + dir.first;
			int ny = p.y + dir.second;

			// Check if the neighboring pixel is within bounds and unvisited
			if (nx >= 0 && nx < width && ny >= 0 && ny < height && !visited[nx][ny] &&
				seedColor.distanceTo(*img.getPixel(nx, ny)) <= tolerance) {
				os.Add(PixelPoint(nx, ny));
				visited[nx][ny] = true;
			}
		}

		// Fill the current pixel and increment frame count
		*img.getPixel(p.x, p.y) = (*colorPicker)(p);
		framecount++;
	}

	// Add final frame and clean up memory
	anim.addFrame(img);
	for (int i = 0; i < width; i++) {
		delete[] visited[i];
	}
	delete[] visited;

	return anim;
}