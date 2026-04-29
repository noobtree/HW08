// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPSController.h"
#include "FPSGameState.h"
#include "PlayerEffectManageComponent.h"
#include "ProjectileActor.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// collision setting
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

	// camera setting
	camera = CreateDefaultSubobject<UCameraComponent>(FName("FirstPersonViewCamera"));	// 컴포넌트 생성
	camera->SetupAttachment(GetCapsuleComponent());		// 컴포넌트 부모관계 설정
	camera->SetRelativeLocation(FVector(-10, 0, BaseEyeHeight));	// 위치 조정
	camera->bUsePawnControlRotation = true;		// 컨트롤러 회전값이 적용되도록 설정
	camera->SetFieldOfView(103);		// FOV 수정

	// firstPersonViewMesh setting
	firstPersonViewMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("FirstPersonViewMesh"));	// 컴포넌트 생성
	firstPersonViewMesh->SetupAttachment(camera);	// 컴포넌트 부모관계 설정
	firstPersonViewMesh->SetRelativeLocationAndRotation(FVector(0, 0, -(BaseEyeHeight + 96)), FRotator(0, -90, 0));		// 위치 조정
	firstPersonViewMesh->SetOnlyOwnerSee(true);		// 자신의 카메라 화면에만 보여지도록 설정
	firstPersonViewMesh->bCastDynamicShadow = false;	// 동적 그림자 제거
	firstPersonViewMesh->SetCastShadow(false);	// 그림자 제거

	// extra setting
	pistolMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("PistolMeshComponent"));
	pistolMesh->SetupAttachment(firstPersonViewMesh, FName("GripPoint"));
	pistolMesh->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	effectManageComponent = CreateDefaultSubobject<UPlayerEffectManageComponent>(FName("EffectManageComponent"));

	// 3인칭 메쉬는 플레이어의 카메라에 노출되지 않도록 설정
	GetMesh()->SetOwnerNoSee(true);
	// 플레이어 태그 추가
	Tags.Add(FName("Player"));

	maxHP = 100;
	currentHP = 100;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	// binding functions to InputAction
	if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AFPSController* fpsController = Cast<AFPSController>(Controller))
		{
			// move
			if (fpsController->moveInputAction != nullptr)
			{
				enhancedInputComponent->BindAction(fpsController->moveInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveAction);
			}

			// jump
			if (fpsController->jumpInputAction != nullptr)
			{
				enhancedInputComponent->BindAction(fpsController->jumpInputAction, ETriggerEvent::Started, this, &ACharacter::Jump);
				enhancedInputComponent->BindAction(fpsController->jumpInputAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
			}

			// look
			if (fpsController->lookInputAction != nullptr)
			{
				enhancedInputComponent->BindAction(fpsController->lookInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LookAction);
			}

			// double jump
			if (fpsController->doubleJumpInputAction != nullptr)
			{
				enhancedInputComponent->BindAction(fpsController->doubleJumpInputAction, ETriggerEvent::Completed, this, &APlayerCharacter::DoubleJumpAction);
			}

			// fly
			if (fpsController->flyInputAction != nullptr)
			{
				enhancedInputComponent->BindAction(fpsController->flyInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::FlyAction);
			}

			// attack
			if (fpsController->fireInputAction != nullptr)
			{
				enhancedInputComponent->BindAction(fpsController->fireInputAction, ETriggerEvent::Started, this, &APlayerCharacter::FirePistolAction);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component!"), *GetNameSafe(this));
	}
}

void APlayerCharacter::MoveAction(const FInputActionValue& value)
{
	if (Controller == nullptr)
	{
		return;
	}

	FVector2D inputVector = value.Get<FVector2D>();

	// 반전 상태인 경우
	if (bIsReversed == true)
	{
		// 입력 반전
		inputVector *= -1;
	}

	AddMovementInput(GetActorForwardVector(), inputVector.X);
	AddMovementInput(GetActorRightVector(), inputVector.Y);
}

void APlayerCharacter::LookAction(const FInputActionValue& value)
{
	if (Controller == nullptr)
	{
		return;
	}

	FVector2D inputVector = value.Get<FVector2D>();

	// 반전 상태인 경우
	if (bIsReversed == true)
	{
		// 입력 반전
		inputVector *= -1;
	}

	AddControllerYawInput(inputVector.X);
	AddControllerPitchInput(inputVector.Y);
}

void APlayerCharacter::DoubleJumpAction()
{
	if (Controller == nullptr)
	{
		return;
	}

	UCharacterMovementComponent* movementComponent = GetCharacterMovement();

	// 공중에 띄워진 상태에서 비행모드 활성화
	if (movementComponent->IsFalling() == true)
	{
		ClientCheatFly();
		return;
	}

	// 비행 중인 경우 비행모드 비활성화
	if (movementComponent->IsFlying() == true)
	{
		ClientCheatWalk();
		return;
	}
}

void APlayerCharacter::FlyAction(const FInputActionValue& value)
{
	if (Controller == nullptr)
	{
		return;
	}

	float inputValue = value.Get<float>();

	AddMovementInput(FVector::UpVector, inputValue);
}

void APlayerCharacter::FirePistolAction()
{
	// G17 -> 17(Magazine) + 1(Chamber)
	// Rsh12 -> 6(Cylinder)
	if (Controller == nullptr || currentHP <= projectileValue)
	{
		return;
	}

	// 발사체를 생성할 위치, 회전 정보 구하기
	FTransform spawnTransform = pistolMesh->GetSocketTransform(FName("Chamber"));
	// 액터 생성 시 옵션 설정
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;	// 객체 소유권자 설정
	spawnParams.Instigator = this;	// 공격자 설정
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// 발사체 생성
	AProjectileActor* projectile = GetWorld()->SpawnActor<AProjectileActor>(projectileActor, spawnTransform.GetLocation(), spawnTransform.Rotator(), spawnParams);

	// 생성된 발사체 확인
	if (projectile != nullptr)
	{
		// 공격자 설정
		projectile->SetAttacker(this);
		// 체력 감소
		currentHP -= bUseHP == true ? projectileValue : 0;

		if (AFPSGameState* gameState = GetWorld()->GetGameState<AFPSGameState>())
		{
			gameState->UpdateHUDWidget();
		}
	}

	if (currentHP <= 0)
	{
		Destroy();
	}
}

void APlayerCharacter::SetReverseInput(bool bNewIsReversed)
{
	if (bIsReversed == bNewIsReversed)
	{
		return;
	}

	// 입력을 반전시키는 플래그 값 변경
	bIsReversed = bNewIsReversed;
}

void APlayerCharacter::SetUseHPForAttack(bool bNewUseHP)
{
	if (bUseHP != bNewUseHP)
	{
		bUseHP = bNewUseHP;
	}
}

float APlayerCharacter::TakeDamage(float damageAmount, const FDamageEvent& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	damageAmount = Super::TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);

	// 데미지 감소 또는 회복 처리
	currentHP -= damageAmount;

	// 최대 또는 최소 체력 값 보장
	currentHP = FMath::Clamp(currentHP, 0, maxHP);

	if (AFPSGameState* gameState = GetWorld()->GetGameState<AFPSGameState>())
	{
		gameState->UpdateHUDWidget();
	}

	// 체력이 0이면 객체 파괴
	if (currentHP == 0)
	{
		Destroy();
	}

	return damageAmount;
}
