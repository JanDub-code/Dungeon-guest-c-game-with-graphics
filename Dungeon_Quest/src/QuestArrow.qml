import QtQuick

Rectangle {
    id: questArrow
    width: 10
    visible: game_engine.active_quest !== null ? game_engine.active_quest.target !== null : false
    enabled: game_engine.active_quest !== null ? game_engine.active_quest.target !== null : false
    transform: Rotation {
        origin.x: 8.5;
        origin.y: 8.5;
        angle: questArrow.getAngle()
    }
    // TODO: Will rotate in relation to player position and quest target

    Image {
        id: arrowImg
        source: "assets/quest_arrow.png"
    }

    function getAngle() {
        if (!game_engine.active_quest) {
            return 0;
        }

        if (game_engine.player && game_engine.active_quest.target) {
            //return game_engine.active_quest.getAngleToTarget();
            var player = game_engine.player;
            var target = game_engine.active_quest.target;
            var dist_x = target.x - player.x;
            var dist_y = target.y - player.y;

            return (Math.atan2(dist_y, dist_x) * 180) / Math.PI;
        }

        return 0;
    }
}
