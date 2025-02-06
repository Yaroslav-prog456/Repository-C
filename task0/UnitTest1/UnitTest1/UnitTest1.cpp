#include "pch.h"
#include "CppUnitTest.h"
#include "../../TreasureHunt/TreasureHunt/Character.h"
#include "../../TreasureHunt/TreasureHunt/Player.h"
#include "../../TreasureHunt/TreasureHunt/Enemy.h"
#include "../../TreasureHunt/TreasureHunt/Character.cpp"
#include "../../TreasureHunt/TreasureHunt/Player.cpp"
#include "../../TreasureHunt/TreasureHunt/Enemy.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		//Тест на корректное создание (Player)
		TEST_METHOD(TestPlayerCreation)
		{
			Player player("Tom", 100, 15, 5);
			Assert::AreEqual(std::string("Tom"), player.getName());
			//Assert::AreEqual(101, player.getHealth());
			//Assert::AreEqual(15, player.getStrength());
			//Assert::AreEqual(5, player.getLevel());
		}
		TEST_METHOD(TestPlayerCreation1)
		{
			Player player("Tom", 100, 15, 5);
			//Assert::AreEqual(std::string("Tom"), player.getName());
			Assert::AreEqual(100, player.getHealth());
			//Assert::AreEqual(15, player.getStrength());
			//Assert::AreEqual(5, player.getLevel());
		}
		TEST_METHOD(TestPlayerCreation2)
		{
			Player player("Tom", 100, 15, 5);
			//Assert::AreEqual(std::string("Tom"), player.getName());
			//Assert::AreEqual(101, player.getHealth());
			Assert::AreEqual(15, player.getStrength());
			//Assert::AreEqual(5, player.getLevel());
		}
		TEST_METHOD(TestPlayerCreation3)
		{
			Player player("Tom", 100, 15, 5);
			//Assert::AreEqual(std::string("Tom"), player.getName());
			//Assert::AreEqual(101, player.getHealth());
			//Assert::AreEqual(15, player.getStrength());
			Assert::AreEqual(5, player.getLevel());
		}

		//Тест enamy сеттер
		TEST_METHOD(TestEnemy)
		{
			Enemy enemy("Undead", 40, 12, EnemyType::Zombie);
			enemy.setType(EnemyType::Dragon);
			Assert::IsTrue(enemy.getType() == EnemyType::Dragon);
		}
		//Тест enamy get
		TEST_METHOD(TestGetEnamy)
		{
			Enemy enemy("Undead", 40, 12, EnemyType::Zombie);
			Assert::AreEqual(std::string("Undead"), enemy.getName());
			Assert::AreEqual(40, enemy.getHealth());
			Assert::AreEqual(12, enemy.getStrength());
			Assert::AreEqual((int)EnemyType::Zombie, (int)enemy.getType());
		}
		TEST_METHOD(TestEnemyAttack)
		{
			Enemy zombie("Zombie", 40, 10, EnemyType::Zombie);
			Enemy skeleton("Skeleton", 30, 8, EnemyType::Skeleton);
			Character target("Target", 50, 0);

			zombie.attack(target); // Zombie damage = 10 + 2 = 12
			Assert::AreEqual(38, target.getHealth());

			target = Character("Target", 50, 0); // Reset target health
			skeleton.attack(target); // Skeleton damage = 8 - 1 = 7
			Assert::AreEqual(43, target.getHealth());
		}

		TEST_METHOD(TestEnemyTakeDamage)
		{
			Enemy zombie("Zombie", 40, 10, EnemyType::Zombie);
			Enemy skeleton("Skeleton", 30, 8, EnemyType::Skeleton);
			int damage = 10;

			zombie.takeDamage(damage); // Zombie takeDamage = 10 - 1 = 9
			Assert::AreEqual(31, zombie.getHealth());

			skeleton.takeDamage(damage); // Skeleton takeDamage = 10 + 1 = 11
			Assert::AreEqual(19, skeleton.getHealth());
		}

		TEST_METHOD(TestDragonAttackAndTakeDamage) {
			Enemy dragon("Dragon", 100, 20, EnemyType::Dragon);
			Character target("Target", 50, 0);

			dragon.attack(target);  // damage = 20 * 2 = 40
			Assert::AreEqual(10, target.getHealth());

			int damage = 10;
			dragon.takeDamage(damage); // damage = 10 / 2 = 5
			Assert::AreEqual(95, dragon.getHealth());

			damage = 1;
			dragon.takeDamage(damage); // damage = 1 / 2 = 0 (целочисленное деление)
			Assert::AreEqual(95, dragon.getHealth());
		}

		TEST_METHOD(TestBossAttackAndTakeDamage) {
			Enemy boss("Boss", 200, 30, EnemyType::Boss);
			Character target("Target", 50, 0);

			boss.attack(target); //damage = 30 + 5 = 35;
			Assert::AreEqual(15, target.getHealth());

			int damage = 20;
			boss.takeDamage(damage); // damage = 20 - 3 = 17;
			Assert::AreEqual(183, boss.getHealth());
		}

		TEST_METHOD(TestPlayerAttack) {
			Player player("Tom", 100, 10, 5);
			Character target("Target", 50, 0);

			player.attack(target);
			Assert::AreEqual(0, target.getHealth());
		}

		TEST_METHOD(TestPlayerAttackWithDifferentLevels) {
			Player player("Hero", 100, 10, 1);
			Character target("Target", 50, 0);

			player.attack(target); // Уровень 1: Урон = 10 * 1 = 10
			Assert::AreEqual(40, target.getHealth());

			player.setLevel(5);
			target = Character("Target", 50, 0); // Сброс здоровья цели
			player.attack(target); // Уровень 5: Урон = 10 * 5 = 50
			Assert::AreEqual(0, target.getHealth());

			player.setLevel(10);
			target = Character("Target", 50, 0); // Сброс здоровья цели
			player.attack(target); // Уровень 10: Урон = 10 * 10 = 100
			Assert::AreEqual(-50, target.getHealth()); //Проверяем урон больше здоровья
		}



	};
}
