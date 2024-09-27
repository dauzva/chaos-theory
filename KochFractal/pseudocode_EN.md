# Algorithm: Koch fractal



### Pseudocode

```pseudo
FUNCTION updateKochPoints
    // Step 1: Clear the existing Koch points
    CLEAR kochPoints

    // Step 2: Get the geometry of the canvas (the rectangle where the Koch curve will be drawn)
    GET the canvas rectangle 'rect'
    GET the coordinates (ax, ay) and dimensions (aw, ah) of the rectangle from 'rect'

    // Step 3: Initialize the starting and ending points of the Koch curve
    APPEND starting point (ax, 2*(ay+ah)/3) to kochPoints
    APPEND ending point (ax+aw, 2*(ay+ah)/3) to kochPoints

    // Save the current points to 'savedKochPoints' for future iterations
    savedKochPoints = kochPoints

    // Step 4: If iteration level is not 0, apply the Koch subdivision
    IF iterationLevel ≠ 0 THEN
        FOR j FROM 0 TO iterationLevel - 1 DO
            // Clear kochPoints for each new iteration
            CLEAR kochPoints
            
            // Step 5: Loop through each line segment in the savedKochPoints
            FOR i FROM 0 TO size(savedKochPoints) - 2 DO
                p = savedKochPoints[i]  // starting point
                APPEND p to kochPoints  // add the current point

                p1 = savedKochPoints[i + 1]  // next point in the sequence
                line = LINE(p, p1)  // create a line between p and p1

                // Step 6: Calculate the points needed to divide the line into 4 segments
                line1 = LINE(p, point at 1/3 along 'line')  // first third of the line
                line21 = LINE(point at 1/3, midpoint)  // line from 1/3 to midpoint
                line22 = normal vector at 2/3 along 'line'  // normal vector at 2/3 of the line

                // Create the peak of the Koch triangle
                peak = POINT(line21.p2.x + line22.p2.x - line1.p2.x, line21.p2.y + line22.p2.y - line1.p2.y)
                line2 = LINE(line1.p2, peak)  // line to peak
                line3 = LINE(peak, point at 2/3 along 'line')  // line from peak to 2/3 along 'line'
                line4 = LINE(point at 2/3, p1)  // final third of the line

                // Step 7: Append the calculated points to the kochPoints
                APPEND line1.p2 to kochPoints (twice)
                APPEND line2.p2 to kochPoints (twice)
                APPEND line3.p2 to kochPoints (twice)
                APPEND line4.p2 to kochPoints
            
            // Step 8: After processing all segments, update savedKochPoints with the new points
            RESIZE savedKochPoints to the size of kochPoints
            savedKochPoints = kochPoints
        END FOR
    END IF
END FUNCTION
```