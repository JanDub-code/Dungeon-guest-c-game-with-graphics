import QtQuick

Item {
    id: worldLevel    
    x: generator.level_origin_x
    y: generator.level_origin_y

    Grid {
            columns: generator.level_w
            rows: generator.level_h
            spacing: 0

            Repeater {
                //model: 25 // TODO connect to CPP
                // generator defined in main.cpp
                model: generator.tiles

                Tile {
                    tileIndex: index
                }
            }
        }
}
