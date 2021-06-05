#include "SpawnerComponent.h"
#include <GameObject.h>
#include <memory>
#include "BallJumperComponent.h"
#include "SingleRowAnimationComponent.h"
#include <ResourceManager.h>
#include <SceneManager.h>
#include <Scene.h>
#include "SlickSamJumperComponent.h"
#include "UggWrongwayJumperComponent.h"
#include <Timer.h>
#include "Qbert.h"
#include "Level.h"	
#include "BaseColliderComponent.h"
#include "CoilyJumperComponent.h"	


SpawnerComponent::SpawnerComponent(cri::GameObject* pOwner, QbertGame* gameManager)
	: BaseComponent(pOwner)
	, m_GameManager(gameManager)
{
	CreateGameObjects();
}

void SpawnerComponent::CreateGameObjects()
{
	auto& scene = cri::SceneManager::GetInstance().GetCurrentScene();

	for (size_t i = 0; i < 4; i++)
	{
		auto redBall = std::make_shared<cri::GameObject>();
		new BallJumperComponent(redBall.get());
		auto texture = new SingleRowAnimationComponent(redBall.get(), 1, 2, cri::ResourceManager::GetInstance().LoadTexture("RedBAllSpriteSheet.png"));
		texture->SetWidth(30.f);
		texture->SetHeight(30.f);
		redBall->Deactivate();

		new BaseColliderComponent(redBall.get(), 15.f, 15.f, Type::Enemy);

		scene.Add(redBall);
		m_RedBallVector.push_back(redBall.get());
	}

	auto slick = std::make_shared<cri::GameObject>();
	(new SlickSamJumperComponent(slick.get()))->AddObserver(m_GameManager);
	auto slickTexture = new SingleRowAnimationComponent(slick.get(), 2, 6, cri::ResourceManager::GetInstance().LoadTexture("SlickSpriteSheet.png"));
	slickTexture->SetWidth(30.f);
	slickTexture->SetHeight(30.f);
	new BaseColliderComponent(slick.get(), 15.f, 15.f, Type::SlickSam);
	slick->Deactivate();
	scene.Add(slick);
	m_GreenCreatureVector.push_back(slick.get());

	auto sam = std::make_shared<cri::GameObject>();
	(new SlickSamJumperComponent(sam.get()))->AddObserver(m_GameManager);
	auto samTexture = new SingleRowAnimationComponent(sam.get(), 2, 6, cri::ResourceManager::GetInstance().LoadTexture("SamSpriteSheet.png"));
	samTexture->SetWidth(30.f);
	samTexture->SetHeight(30.f);
	new BaseColliderComponent(sam.get(), 15.f, 15.f, Type::SlickSam);
	sam->Deactivate();
	scene.Add(sam);
	m_GreenCreatureVector.push_back(sam.get());

	auto ugg = std::make_shared<cri::GameObject>();
	auto uggJumper = new UggWrongwayJumperComponent(ugg.get());
	uggJumper->SetGoingRight(false);
	auto uggTexture = new SingleRowAnimationComponent(ugg.get(), 2, 4, cri::ResourceManager::GetInstance().LoadTexture("UggSpriteSheet.png"));
	uggTexture->SetWidth(30.f);
	uggTexture->SetHeight(30.f);
	new BaseColliderComponent(ugg.get(), 15.f, 15.f, Type::Enemy);
	ugg->Deactivate();
	scene.Add(ugg);
	m_PurpleCreatureVector.push_back(ugg.get());

	auto wrongway = std::make_shared<cri::GameObject>();
	auto wrongwayJumper = new UggWrongwayJumperComponent(wrongway.get());
	wrongwayJumper->SetGoingRight(true);
	auto wrongwayTexture = new SingleRowAnimationComponent(wrongway.get(), 2, 4, cri::ResourceManager::GetInstance().LoadTexture("WrongwaySpriteSheet.png"));
	wrongwayTexture->SetWidth(30.f);
	wrongwayTexture->SetHeight(30.f);
	new BaseColliderComponent(wrongway.get(), 15.f, 15.f, Type::Enemy);
	wrongway->Deactivate();
	scene.Add(wrongway);
	m_PurpleCreatureVector.push_back(wrongway.get());


	m_Coily = std::make_shared<cri::GameObject>();
	m_Coily->Deactivate();

	auto coilyTextureComp = new SingleRowAnimationComponent(m_Coily.get(), 4, 2, cri::ResourceManager::GetInstance().LoadTexture("CoilySpriteSheet.png"));
	coilyTextureComp->SetWidth(30.f);
	coilyTextureComp->SetHeight(60.f);
	coilyTextureComp->m_RelativeTransform.SetPosition(0, -10, 0);
	coilyTextureComp->SetAnimation(2);
	coilyTextureComp->SetDoRender(false);

	auto coilyBallTextureComp = new SingleRowAnimationComponent(m_Coily.get(), 1, 2, cri::ResourceManager::GetInstance().LoadTexture("CoilyBallSpriteSheet.png"));
	coilyBallTextureComp->SetWidth(30.f);
	coilyBallTextureComp->SetHeight(30.f);
	coilyBallTextureComp->SetAnimation(0);


	new BaseColliderComponent(m_Coily.get(), 15.f, 15.f, Type::Enemy);

	auto coilyJumperComponent = new CoilyJumperComponent(m_Coily.get(), m_GameManager->GetQbert1(), m_GameManager->GetQbert2());
	coilyJumperComponent->SetIsPlayerControlled(false);

	scene.Add(m_Coily);


}

void SpawnerComponent::Update()
{
	auto deltaTime = Timer::GetInstance()->GetElapsed();
	m_BallSpawnCounter += deltaTime;
	m_GreenSpawnCounter += deltaTime;
	m_PurpleSpawnCounter += deltaTime;
	m_CoilySpawnCounter += deltaTime;


	if (m_BallSpawnCounter > m_BallSpawnInterval)
	{
		SpawnBall();
		m_BallSpawnCounter -= m_BallSpawnInterval;
	}
	if (m_GreenSpawnCounter > m_GreenSpawnInerval)
	{
		SpawnGreenCreature();
		m_GreenSpawnCounter -= m_GreenSpawnInerval;
	}
	if (m_PurpleSpawnCounter > m_PurpleSpawnInterval)
	{
		SpawnPurpleCreature();
		m_PurpleSpawnCounter -= m_PurpleSpawnInterval;
	}
	if (m_CoilySpawnCounter > m_CoilySpawnDelay)
	{
		SpawnCoily();
	}
}

void SpawnerComponent::SpawnBall()
{
	auto ballIt = std::find_if(m_RedBallVector.begin(), m_RedBallVector.end(), [](cri::GameObject* ball) {return !ball->IsActive(); });
	if (ballIt != m_RedBallVector.end())
	{
		(*ballIt)->Activate();
		(*ballIt)->GetComponent<BallJumperComponent>()->SetStartPos(m_GameManager->GetLevel(), 1, std::rand()%2);
	}
}

void SpawnerComponent::SpawnGreenCreature()
{
	auto greenIt = std::find_if(m_GreenCreatureVector.begin(), m_GreenCreatureVector.end(), [](cri::GameObject* green) {return !green->IsActive(); });
	if (greenIt != m_GreenCreatureVector.end())
	{
		(*greenIt)->Activate();
		(*greenIt)->GetComponent<SlickSamJumperComponent>()->SetStartPos(m_GameManager->GetLevel(), 1, std::rand() % 2);
	}
}

void SpawnerComponent::SpawnPurpleCreature()
{
	auto purpleIt = std::find_if(m_PurpleCreatureVector.begin(), m_PurpleCreatureVector.end(), [](cri::GameObject* purple) {return !purple->IsActive(); });
	if (purpleIt != m_PurpleCreatureVector.end())
	{
		auto jumperComp = (*purpleIt)->GetComponent<UggWrongwayJumperComponent>();
		(*purpleIt)->Activate();
		jumperComp->SetStartPos(m_GameManager->GetLevel(), m_GameManager->GetLevel()->GetHeight()-1, int(!jumperComp->GetGoingRight())* (m_GameManager->GetLevel()->GetHeight() - 1)); //bottom left or bottom right
	}
}

void SpawnerComponent::SpawnCoily()
{
	if (m_Coily->IsActive())
	{
		return;
	}
	auto jumperComp = m_Coily->GetComponent<CoilyJumperComponent>();
	m_Coily->Activate();
	jumperComp->SetStartPos(m_GameManager->GetLevel(), 1, std::rand() % 2);
}

void SpawnerComponent::ResetAll()
{
	for (auto gameObject : m_RedBallVector)
	{
		gameObject->GetComponent<SingleRowAnimationComponent>()->SetFrame(0);
		gameObject->Deactivate();
	}
	for (auto gameObject : m_GreenCreatureVector)
	{
		gameObject->GetComponent<SingleRowAnimationComponent>()->SetFrame(0);
		gameObject->Deactivate();
	}
	for (auto gameObject : m_PurpleCreatureVector)
	{
		gameObject->GetComponent<SingleRowAnimationComponent>()->SetFrame(0);
		gameObject->Deactivate();
	}

	m_Coily->Deactivate();
	m_Coily->GetComponent<SingleRowAnimationComponent>()->SetFrame(0);
	m_Coily->GetComponent<CoilyJumperComponent>()->SetIsEgg(true);

	m_BallSpawnCounter = 0.f;
	m_GreenSpawnCounter = 0.f;
	m_PurpleSpawnCounter = 0.f;
	m_CoilySpawnCounter = 0.f;
}
