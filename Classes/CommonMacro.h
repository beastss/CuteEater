#ifndef __COMMON_MACRO_H__
#define __COMMON_MACRO_H__

#define NOTIFY_VIEWS(_FUNC_ ,...)						\
for (size_t index = 0; index < m_views.size(); ++index) \
{														\
	m_views[index]->_FUNC_(__VA_ARGS__);				\
}

#define INIT_SNAKE_LENGTH 6
#define NORMAL_SPEED 250
#define GAME_LAYER_WIDTH 2420
#define GAME_LAYER_HEIGHT 2145
#define SNAKE_NUM 3
#define MIN_FOOD_NUM 500
enum TouchPriority
{
	kTouchPriorityPanel = -10,
	kTouchPriorityDialog = -20,
};
#endif