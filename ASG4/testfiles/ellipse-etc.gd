# $Id: ellipse-etc.gd,v 1.2 2014-08-04 18:17:15-07 - - $
# Test ellipse, polygon, and a few things.
define first ellipse 200 400
define second ellipse 400 200
define third circle 100
define test square 100
define test2 rectangle 100 200
define poly polygon 0 0 10 -2 20 0 22 10 20 20 10 22 0 20 -2 10
draw blue poly 300 300
draw cyan first 300 300
draw yellow second 300 300
draw black third 300 300
draw blue test2 400 300
draw red test 100 200
