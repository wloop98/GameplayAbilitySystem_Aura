// Copyright Wloop


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	//角色会根据移动方向自动调整旋转角度
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//设置角色绕Yaw轴（垂直轴）的旋转速率为400度/秒。较高的值使角色转向更灵敏，较低的转向更平滑 
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	//限制角色只能在指定平面（如X-Y平面）移动，避免垂直方向（Z轴）偏移
	GetCharacterMovement()->bConstrainToPlane = true;
	//角色生成时自动对齐到约束平面，确保初始位置符合平面规则
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//禁用控制器对角色旋转的直接控制。角色旋转仅由移动方向决定（通过 bOrientRotationToMovement），而摄像机或控制器可独立旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}
