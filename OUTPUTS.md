# Final Project Outputs & Deliverables

The AgriProbe system translates raw sensor telemetry into actionable, precision agriculture outputs for farm managers and autonomous tractors:

## 1. Real-Time Depth-Force Telemetry
* **Live Web Dashboard:** Renders real-time depth-versus-penetration force curves during probe insertion.
* **Status Flags:** Instant safety triggers displaying **Normal**, **Hardpan Detected**, or **Obstacle Abort** on the UI.

## 2. 3D Subsurface Mapping & Spatial Interpolation
* **Kriging Interpolation:** Uses Python and Ordinary Kriging algorithms applied to $(X, Y, Z)$ spatial coordinate telemetry.
* **Spatial Visualizations:** Generates 3D volumetric heatmaps and 2D raster maps showing how soil compaction, moisture, and organic matter vary across fields.

## 3. Variable-Rate Tillage (VRT) Prescriptions
* **Actionable Prescriptions:** Exports standardized **GeoTIFF** and **Shapefile** map layers.
* **Precision Subsoiling:** Directs automated tractors to rip the soil *only* where hardpan layers exist, optimizing diesel consumption and protecting soil structure.
