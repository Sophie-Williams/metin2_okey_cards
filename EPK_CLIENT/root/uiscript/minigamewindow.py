import uiScriptLocale

TAKE_ROOT = "d:/ymir work/ui/minigame/rumi/"

window = {
	"name" : "MiniGameWindow",
	
	"x" : SCREEN_WIDTH - 136 - 100,
	"y" : 15,
	
	"width" : 100,
	"height" : 58,
	
	"children" :
	(
		{
			"name" : "mini_game_window",
			"type" : "window",
			
			"x" : 0,
			"y" : 0,
			
			"width" : 100,
			"height" : 58,
			
			"children" :
			(
				{
					"name" : "minigame_rumi_button",
					"type" : "button",
					
					"x" : 0,
					"y" : 0,


					"tooltip_text" : uiScriptLocale.MINI_GAME_RUMI_TITLE,
					"tooltip_x" : -2,
					"tooltip_y" : 55,
					
					"default_image" : TAKE_ROOT + "rumi_button_min.sub",
					"over_image" : TAKE_ROOT + "rumi_button_min.sub",
					"down_image" : TAKE_ROOT + "rumi_button_min.sub",
				},
			),
		},		
	),	
}
