#ifndef taskbar_position_h__
#define taskbar_position_h__

#include <Windows.h>


namespace cactus
{


enum emTaskbarPosition {
    TaskballPositionInvaild,
    TaskballPositionLeft,
    TaskballPositionRight,
    TaskballPositionTop,
    TaskballPositionBottom,
    TaskballPositionHide
};
/**
 * @brief ��ȡ��������λ��
 * @return �ɹ�������������λ��
 * @see SystemParametersInfo
 */
static emTaskbarPosition GetTaskbarPosition();


}

#endif // taskbar_position_h__
