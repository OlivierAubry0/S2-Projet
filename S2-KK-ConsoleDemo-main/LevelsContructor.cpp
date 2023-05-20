#include "LevelsContructor.h"
#include <random>

std::string AutoLeft = "ab";
std::string AutoRight = "ji";
std::string LimoLeft = "cde";
std::string LimoRight = "mdk";

int LevelsContructor::MuonsCount = 0;
std::string TruckLeft(int centerCount) 
{
    std::string content = "f";
    for (int i = 0; i < centerCount; i++)
    {
        content += "g";
    }
    return content + "h";
}
std::string TruckRight(int centerCount)
{
    std::string content = "p";
    for (int i = 0; i < centerCount; i++)
    {
        content += "g";
    }
    return content + "n";
}
//Convention pour les niveaux:

//Nomenclature: les rows ont un indice allant de 1 au nombre de rows actives (1 en haut)
// Les game objects et les hitboxes ont la notation hAB et gAB, o� A est le num�ro de rang�e et B est le num�ro dans la rang�e
// OM: occupation maximale d'une rang�e (nombre de cases occup�es par l'ensemble des objets sur un total de 40 cases de large)
// N: nombre de rangees actives dans un niveau 
// 
// Nombre total de niveaux: 6
// Dimensions: 20 rang�es et 40 colonnes
// Objets fixes: � partir du niveau 3
// Syst�me de pointage: pointsNiveau=rang�esParcourues*Niveau/2 et pointsTotaux=somme(pointsNiveau)
//1: Vitesse entre 1800 et 2200, OM==10/40, N==9.
//2: Vitesse entre 1500 et 1900, OM==15/40, N==10.
//3: Vitesse entre 1300 et 1700, OM==15/40, N==11.
//4: Vitesse entre 1100 et 1500, OM==18/40, N==12
//5: Vitesse entre 1100 et 1500, OM==18/40, N==13
//6: Vitesse entre 900 et 1300, OM==22/40, N==13
/*
Gauche :

- Auto
	- "ab"
- Limo
	- "cde"
-Truck
	- "fgggh"

Droite :

- Auto
	- "ij"
- Limo
	- "kdm"
-Truck
	- "ngggp"
*/

Row BlockerSideRow() 
{
    //Blocker sides
    Hitbox h911 = Hitbox({ 0,0 }, "XXXXXXXXXXXXXXX");
    Hitbox h912 = Hitbox({ 25,0 }, "XXXXXXXXXXXXXXX");
    GameObject g9101 = GameObject(h911, 'X', Obstacle);
    GameObject g9102 = GameObject(h912, 'X', Obstacle);
    Row rowBlockerSide(0 * multiplier, Direction::LEFT);
    rowBlockerSide.add(g9101);
    rowBlockerSide.add(g9102);
    return rowBlockerSide;
}
Row BlockerCenterRow()
{
    //Blocker sides
    Hitbox h911 = Hitbox({ 15,0 }, "XXXXXXXXXX");
    GameObject g911 = GameObject(h911, 'X', Obstacle);
    GameObject g9101 = GameObject(h911, 'X', Obstacle);
    Row rowBlockerSide(0 * multiplier, Direction::LEFT);
    rowBlockerSide.add(g9101);
    return rowBlockerSide;
}
Row BlockerMultipleRow()
{
    //Blocker sides
    Hitbox h911 = Hitbox({ 3,0 }, "XXXXX");
    Hitbox h912 = Hitbox({ 15,0 }, "XXXXXXXXXX");
    Hitbox h913 = Hitbox({ 32,0 }, "XXXXX");
    GameObject g911 = GameObject(h911, 'X', Obstacle);
    GameObject g9101 = GameObject(h912, 'X', Obstacle);
    GameObject g9102 = GameObject(h913, 'X', Obstacle);
    Row rowBlockerSide(0 * multiplier, Direction::LEFT);
    rowBlockerSide.add(g911);
    rowBlockerSide.add(g9101);
    rowBlockerSide.add(g9102);
    return rowBlockerSide;
}
Row PowerUPRow() 
{
    clock_t now = clock();
    unsigned int seed = LevelsContructor::MuonsCount ^ 2 * now;
    srand(seed);
    int pos = rand() % 40;
    //Blocker sides
    Hitbox h911 = Hitbox({ pos,0 }, "$");
    GameObject g911 = GameObject(h911, '$', Powerup);
    Row rowBlockerSide(0 * multiplier, Direction::LEFT);
    rowBlockerSide.add(g911);
    return rowBlockerSide;
}


Level LevelsContructor::Level1()
{
    //Empty row (r�utilis�e plusieurs fois)
    Row empty(0, Direction::LEFT);

    //Row 1
    Hitbox h11 = Hitbox({ 0,1 }, AutoLeft);
    GameObject g11 = GameObject(h11, '@');
    Hitbox h12 = Hitbox({ 20,1 }, TruckLeft(3));
    GameObject g12 = GameObject(h12, '@');
    Row row1(2000 * multiplier, Direction::LEFT);
    row1.add(g11);
    row1.add(g12);

    //Row 2
    Hitbox h21 = Hitbox({ WIDTH / 2,3 }, TruckRight(3));
    GameObject g21 = GameObject(h21, '@');
    Row row2(1800 * multiplier, Direction::RIGHT);
    row2.add(g21);

    //Row 3
    Hitbox h31 = Hitbox({ WIDTH / 2,5 }, TruckRight(4));
    GameObject g31 = GameObject(h31, '@');
    Row row3(2000 * multiplier, Direction::RIGHT);
    row3.add(g31);

    //Row 4
    Hitbox h41 = Hitbox({ WIDTH / 2,7 }, TruckLeft(5));
    GameObject g41 = GameObject(h41, '@');
    Row row4(2200 * multiplier, Direction::LEFT);
    Hitbox h42 = Hitbox({0,7 }, LimoLeft);
    GameObject g42 = GameObject(h42, '@');
    row4.add(g41);
    row4.add(g42);
    
    //Row 5
    Hitbox h51 = Hitbox({ WIDTH / 2,9 }, TruckLeft(4));
    GameObject g51 = GameObject(h51, '@');
    Row row5(1800 * multiplier, Direction::LEFT);
    row5.add(g51);

    //Row 6
    Hitbox h61 = Hitbox({ WIDTH / 2,11 }, TruckRight(3));
    GameObject g61 = GameObject(h61, '@');
    Row row6(2200 * multiplier, Direction::RIGHT);
    row6.add(g61);

    //Row 7
    Hitbox h71 = Hitbox({ WIDTH / 2,13 }, TruckLeft(4));
    GameObject g71 = GameObject(h71, '@');
    Row row7(2000 * multiplier, Direction::LEFT);
    row7.add(g71);

    //Row 8
    Hitbox h81 = Hitbox({ WIDTH / 2,15 }, LimoRight);
    GameObject g81 = GameObject(h81, '@');
    Row row8(2100 * multiplier, Direction::RIGHT);
    row8.add(g81);

    //Row 9
    Hitbox h91 = Hitbox({ 1,17 }, TruckLeft(3));
    GameObject g93 = GameObject(h91, '@');
    Hitbox h92 = Hitbox({ 24,17 }, TruckLeft(3));
    GameObject g92 = GameObject(h92, '@');
    Row row9(1800 * multiplier, Direction::LEFT);
    row9.add(g92);
    row9.add(g93);

    

    //Construction de level 1
    Level level;
    level.addRow(empty);
    level.addRow(row1);
    level.addRow(empty);
    level.addRow(row2);
    level.addRow(empty);
    level.addRow(row3);
    level.addRow(empty);
    level.addRow(row4);
    level.addRow(BlockerCenterRow());
    level.addRow(row5);
    level.addRow(empty);
    level.addRow(row6);
    level.addRow(empty);
    level.addRow(row7);
    level.addRow(empty);
    level.addRow(row8);
    level.addRow(BlockerSideRow());
    level.addRow(empty);
    level.addRow(row9);
    level.addRow(empty);
    return level;
}

Level LevelsContructor::Level2()
{
    //Empty row (r�utilis�e plusieurs fois)
    Row empty(0, Direction::LEFT);

    //Row 1
    Hitbox h11 = Hitbox({ 0,1 }, TruckLeft(5));
    GameObject g11 = GameObject(h11, '@');
    Hitbox h12 = Hitbox({ 28,1 }, LimoLeft);
    GameObject g12 = GameObject(h12, '@');
    Row row1(1700 * multiplier, Direction::LEFT);
    Hitbox h13 = Hitbox({ 15,1 }, AutoLeft);
    GameObject g13 = GameObject(h13, '@');
    row1.add(g11);
    row1.add(g12);
    row1.add(g13);

    //Row 2
    Hitbox h21 = Hitbox({ WIDTH / 2,3 }, TruckRight(10));
    GameObject g21 = GameObject(h21, '@');
    Row row2(1800 * multiplier, Direction::RIGHT);
    row2.add(g21);

    //Row 3
    Hitbox h31 = Hitbox({ WIDTH / 2,5 }, TruckRight(6));
    GameObject g31 = GameObject(h31, '@');
    Row row3(1500 * multiplier, Direction::RIGHT);
    row3.add(g31);

    //Row 4
    Hitbox h41 = Hitbox({ WIDTH / 2,7 }, LimoLeft);
    GameObject g41 = GameObject(h41, '@');
    Row row4(1900 * multiplier, Direction::LEFT);
    Hitbox h42 = Hitbox({ 0,7 }, AutoLeft);
    GameObject g42 = GameObject(h42, '@');
    row4.add(g41);
    row4.add(g42);

    //Row 5
    Hitbox h51 = Hitbox({ WIDTH / 2,9 }, TruckLeft(4));
    GameObject g51 = GameObject(h51, '@');
    Row row5(1500 * multiplier, Direction::LEFT);
    row5.add(g51);

    //Row 6
    Hitbox h61 = Hitbox({ WIDTH / 2,11 }, TruckRight(7));
    GameObject g61 = GameObject(h61, '@');
    Row row6(1900 * multiplier, Direction::RIGHT);
    row6.add(g61);

    //Row 7
    Hitbox h71 = Hitbox({ WIDTH / 2,13 }, TruckLeft(4));
    GameObject g71 = GameObject(h71, '@');
    Row row7(1700 * multiplier, Direction::LEFT);
    row7.add(g71);

    //Row 8
    Hitbox h81 = Hitbox({ WIDTH / 2,15 }, TruckRight(10));
    GameObject g81 = GameObject(h81, '@');
    Row row8(1800 * multiplier, Direction::RIGHT);
    row8.add(g81);

    //Row 9
    Hitbox h91 = Hitbox({ 1,17 }, TruckLeft(5));
    GameObject g91 = GameObject(h91, '@');
    Hitbox h92 = Hitbox({ 24,17 }, TruckLeft(3));
    GameObject g92 = GameObject(h92, '@');
    Row row9(1500 * multiplier, Direction::LEFT);
    row9.add(g91);
    row9.add(g92);

    //Row 10
    Hitbox h101 = Hitbox({ 10,17 }, LimoRight);
    GameObject g101 = GameObject(h101, '@');
    Row row10(1700 * multiplier, Direction::RIGHT);
    row10.add(g101);

    //Construction de level 2
    Level level;
    level.addRow(empty);
    level.addRow(row1);
    level.addRow(empty);
    level.addRow(row2);
    level.addRow(empty);
    level.addRow(row3);
    level.addRow(empty);
    level.addRow(row4);
    level.addRow(BlockerCenterRow());
    level.addRow(row5);
    level.addRow(BlockerSideRow());
    level.addRow(row6);
    level.addRow(empty);
    level.addRow(row7);
    level.addRow(empty);
    level.addRow(row8);
    level.addRow(row9);
    level.addRow(empty);
    level.addRow(row10);
    level.addRow(empty);
    return level;
}
Level LevelsContructor::Level3()
{
    //Empty row (r�utilis�e plusieurs fois)
    Row empty(0, Direction::LEFT);

    //Row 1
    Hitbox h11 = Hitbox({ 0,1 }, TruckLeft(5));
    GameObject g11 = GameObject(h11, '@');
    Hitbox h12 = Hitbox({ 28,1 }, LimoLeft);
    GameObject g12 = GameObject(h12, '@');
    Row row1(1500 * multiplier, Direction::LEFT);
    Hitbox h13 = Hitbox({ 15,1 }, AutoLeft);
    GameObject g13 = GameObject(h13, '@');
    row1.add(g11);
    row1.add(g12);
    row1.add(g13);

    //Row 2
    Hitbox h21 = Hitbox({ WIDTH / 2,3 }, TruckRight(10));
    GameObject g21 = GameObject(h21, '@');
    Row row2(1600 * multiplier, Direction::RIGHT);
    row2.add(g21);

    //Row 3
    Hitbox h31 = Hitbox({ WIDTH / 2,5 }, TruckRight(6));
    GameObject g31 = GameObject(h31, '@');
    Row row3(1300 * multiplier, Direction::RIGHT);
    row3.add(g31);

    //Row 4
    Hitbox h41 = Hitbox({ WIDTH / 2,7 }, TruckLeft(7));
    GameObject g41 = GameObject(h41, '@');
    Row row4(1700 * multiplier, Direction::LEFT);
    Hitbox h42 = Hitbox({ 0,7 }, LimoLeft);
    GameObject g42 = GameObject(h42, '@');
    row4.add(g41);
    row4.add(g42);

    //Row 5
    Hitbox h51 = Hitbox({ WIDTH / 2,9 }, TruckLeft(4));
    GameObject g51 = GameObject(h51, '@');
    Row row5(1300 * multiplier, Direction::LEFT);
    row5.add(g51);

    //Row 6
    Hitbox h61 = Hitbox({ WIDTH / 2,11 }, TruckRight(7));
    GameObject g61 = GameObject(h61, '@');
    Row row6(1700 * multiplier, Direction::RIGHT);
    row6.add(g61);

    //Row 7
    Hitbox h71 = Hitbox({ WIDTH / 2,13 }, LimoLeft);
    GameObject g71 = GameObject(h71, '@');
    Row row7(1500 * multiplier, Direction::LEFT);
    row7.add(g71);

    //Row 8
    Hitbox h81 = Hitbox({ WIDTH / 2,15 }, TruckRight(10));
    GameObject g81 = GameObject(h81, '@');
    Row row8(1600 * multiplier, Direction::RIGHT);
    row8.add(g81);

    //Row 9
    Hitbox h91 = Hitbox({ 1,17 }, TruckLeft(5));
    GameObject g91 = GameObject(h91, '@');
    Hitbox h92 = Hitbox({ 24,17 }, LimoLeft);
    GameObject g92 = GameObject(h92, '@');
    Row row9(1300 * multiplier, Direction::LEFT);
    row9.add(g91);
    row9.add(g92);

    //Row 10
    Hitbox h101 = Hitbox({ 10,17 }, TruckLeft(5));
    GameObject g101 = GameObject(h101, '@');
    Row row10(1500 * multiplier, Direction::LEFT);
    row10.add(g101);

    //Row 11
    Hitbox h111 = Hitbox({ 20,17 }, TruckLeft(5));
    GameObject g111 = GameObject(h111, '@');
    Hitbox h112 = Hitbox({ 0,17 }, TruckLeft(3));
    GameObject g112 = GameObject(h112, '@');
    Row row11(1700 * multiplier, Direction::LEFT);
    row11.add(g111);
    row11.add(g112);

    //Construction de level 3
    Level level;
    level.addRow(empty);
    level.addRow(row1);
    level.addRow(empty);
    level.addRow(row2);
    level.addRow(row3);
    level.addRow(empty);
    level.addRow(row4);
    level.addRow(row5);
    level.addRow(BlockerCenterRow());
    level.addRow(row6);
    level.addRow(BlockerSideRow());
    level.addRow(row7);
    level.addRow(BlockerCenterRow());
    level.addRow(row8);
    level.addRow(PowerUPRow());
    level.addRow(row9);
    level.addRow(row10);
    level.addRow(empty);
    level.addRow(row11);
    level.addRow(empty);
    return level;
}
Level LevelsContructor::Level4()
{
    //Empty row (r�utilis�e plusieurs fois)
    Row empty(0, Direction::LEFT);

    //Row 1
    Hitbox h11 = Hitbox({ 0,1 }, TruckLeft(5));
    GameObject g11 = GameObject(h11, '@');
    Hitbox h12 = Hitbox({ 28,1 }, LimoLeft);
    GameObject g12 = GameObject(h12, '@');
    Row row1(1300 * multiplier, Direction::LEFT);
    Hitbox h13 = Hitbox({ 15,1 }, AutoLeft);
    GameObject g13 = GameObject(h13, '@');
    row1.add(g11);
    row1.add(g12);
    row1.add(g13);

    //Row 2
    Hitbox h21 = Hitbox({ WIDTH / 2,3 }, TruckRight(10));
    GameObject g21 = GameObject(h21, '@');
    Row row2(1400 * multiplier, Direction::RIGHT);
    row2.add(g21);

    //Row 3
    Hitbox h31 = Hitbox({ WIDTH / 2,5 }, TruckRight(12));
    GameObject g31 = GameObject(h31, '@');
    Row row3(1100 * multiplier, Direction::RIGHT);
    row3.add(g31);

    //Row 4
    Hitbox h41 = Hitbox({ WIDTH / 2,7 }, TruckLeft(7));
    GameObject g41 = GameObject(h41, '@');
    Row row4(1500 * multiplier, Direction::LEFT);
    Hitbox h42 = Hitbox({ 0,7 }, LimoLeft);
    GameObject g42 = GameObject(h42, '@');
    row4.add(g41);
    row4.add(g42);

    //Row 5
    Hitbox h51 = Hitbox({ WIDTH / 2,9 }, TruckLeft(4));
    GameObject g51 = GameObject(h51, '@');
    Row row5(1100 * multiplier, Direction::LEFT);
    row5.add(g51);

    //Row 6
    Hitbox h61 = Hitbox({ WIDTH / 2,11 }, TruckRight(7));
    GameObject g61 = GameObject(h61, '@');
    Hitbox h62 = Hitbox({ 0,11 }, TruckRight(7));
    GameObject g62 = GameObject(h62, '@');
    Row row6(1500 * multiplier, Direction::RIGHT);
    row6.add(g61);
    row6.add(g62);

    //Row 7
    Hitbox h71 = Hitbox({ WIDTH / 2,13 }, TruckLeft(4));
    GameObject g71 = GameObject(h71, '@');
    Row row7(1300 * multiplier, Direction::LEFT);
    row7.add(g71);

    //Row 8
    Hitbox h81 = Hitbox({ WIDTH / 2,15 }, TruckRight(10));
    GameObject g81 = GameObject(h81, '@');
    Row row8(1400 * multiplier, Direction::RIGHT);
    row8.add(g81);

    //Row 9
    Hitbox h91 = Hitbox({ 1,17 }, TruckLeft(5));
    GameObject g91 = GameObject(h91, '@');
    Hitbox h92 = Hitbox({ 24,17 }, LimoLeft);
    GameObject g92 = GameObject(h92, '@');
    Row row9(1100 * multiplier, Direction::LEFT);
    row9.add(g91);
    row9.add(g92);

    //Row 10
    Hitbox h101 = Hitbox({ 10,17 }, TruckLeft(5));
    GameObject g101 = GameObject(h101, '@');
    Row row10(1500 * multiplier, Direction::LEFT);
    row10.add(g101);

    //Row 11
    Hitbox h111 = Hitbox({ 20,17 }, LimoLeft);
    GameObject g111 = GameObject(h111, '@');
    Hitbox h112 = Hitbox({ 0,17 }, LimoLeft);
    GameObject g112 = GameObject(h112, '@');
    Row row11(1300 * multiplier, Direction::LEFT);
    row11.add(g111);
    row11.add(g112);

    //Row 12
    Hitbox h121 = Hitbox({ 20,17 }, TruckLeft(5));
    GameObject g121 = GameObject(h121, '@');
    Row row12(1500 * multiplier, Direction::LEFT);
    row12.add(g121);

    //Construction de level 4
    Level level;
    level.addRow(empty);
    level.addRow(row1);
    level.addRow(empty);
    level.addRow(row2);
    level.addRow(row3);
    level.addRow(empty);
    level.addRow(row4);
    level.addRow(empty);
    level.addRow(row5);
    level.addRow(BlockerCenterRow());
    level.addRow(row6);
    level.addRow(row7);
    level.addRow(BlockerSideRow());
    level.addRow(row8);
    level.addRow(row9);
    level.addRow(PowerUPRow());
    level.addRow(row10);
    level.addRow(row11);
    level.addRow(row12);
    level.addRow(empty);
    return level;
}
Level LevelsContructor::Level5()
{
    //Empty row (r�utilis�e plusieurs fois)
    Row empty(0, Direction::LEFT);

    //Row 1
    Hitbox h11 = Hitbox({ 0,1 }, TruckLeft(5));
    GameObject g11 = GameObject(h11, '@');
    Hitbox h12 = Hitbox({ 28,1 }, LimoLeft);
    GameObject g12 = GameObject(h12, '@');
    Row row1(1300 * multiplier, Direction::LEFT);
    Hitbox h13 = Hitbox({ 15,1 }, AutoLeft);
    GameObject g13 = GameObject(h13, '@');
    row1.add(g11);
    row1.add(g12);
    row1.add(g13);

    //Row 2
    Hitbox h21 = Hitbox({ 20,17 }, TruckLeft(5));
    GameObject g21 = GameObject(h21, '@');
    Row row2(1500 * multiplier, Direction::LEFT);
    row2.add(g21);

    //Row 3
    Hitbox h31 = Hitbox({ WIDTH / 2,3 }, AutoRight);
    GameObject g31 = GameObject(h31, '@');
    Row row3(1400 * multiplier, Direction::RIGHT);
    row3.add(g31);

    //Row 4
    Hitbox h41 = Hitbox({ WIDTH / 2,5 }, TruckRight(12));
    GameObject g41 = GameObject(h41, '@');
    Row row4(1100 * multiplier, Direction::RIGHT);
    row4.add(g41);

    //Row 5
    Hitbox h51 = Hitbox({ WIDTH / 2,7 }, TruckLeft(7));
    GameObject g51 = GameObject(h51, '@');
    Row row5(1500 * multiplier, Direction::LEFT);
    Hitbox h52 = Hitbox({ 0,7 }, LimoLeft);
    GameObject g52 = GameObject(h52, '@');
    row5.add(g51);
    row5.add(g52);

    //Row 6
    Hitbox h61 = Hitbox({ WIDTH / 2,9 }, TruckLeft(4));
    GameObject g61 = GameObject(h61, '@');
    Row row6(1100 * multiplier, Direction::LEFT);
    row6.add(g61);

    //Row 7
    Hitbox h71 = Hitbox({ WIDTH / 2,11 }, TruckRight(7));
    GameObject g71 = GameObject(h71, '@');
    Hitbox h72 = Hitbox({ 0,11 }, TruckRight(7));
    GameObject g72 = GameObject(h72, '@');
    Row row7(1500 * multiplier, Direction::RIGHT);
    row7.add(g71);
    row7.add(g72);

    //Row 8
    Hitbox h81 = Hitbox({ WIDTH / 2,13 }, LimoLeft);
    GameObject g81 = GameObject(h81, '@');
    Row row8(1300 * multiplier, Direction::LEFT);
    row8.add(g81);

    //Row 9
    Hitbox h91 = Hitbox({ WIDTH / 2,15 }, TruckRight(10));
    GameObject g91 = GameObject(h91, '@');
    Row row9(1400 * multiplier, Direction::RIGHT);
    row9.add(g91);

    //Row 10
    Hitbox h101 = Hitbox({ 1,17 }, TruckLeft(5));
    GameObject g101 = GameObject(h101, '@');
    Hitbox h102 = Hitbox({ 24,17 }, LimoLeft);
    GameObject g102 = GameObject(h102, '@');
    Row row10(1100 * multiplier, Direction::LEFT);
    row10.add(g101);
    row10.add(g102);

    //Row 11
    Hitbox h111 = Hitbox({ 10,17 }, TruckLeft(5));
    GameObject g111 = GameObject(h111, '@');
    Row row11(1500 * multiplier, Direction::LEFT);
    row11.add(g111);

    //Row 12
    Hitbox h121 = Hitbox({ 20,17 }, LimoLeft);
    GameObject g121 = GameObject(h121, '@');
    Hitbox h122 = Hitbox({ 0,17 }, LimoLeft);
    GameObject g122 = GameObject(h122, '@');
    Row row12(1300 * multiplier, Direction::LEFT);
    row12.add(g121);
    row12.add(g122);

    //Row 13
    Hitbox h131 = Hitbox({ 20,17 }, TruckLeft(5));
    GameObject g131 = GameObject(h131, '@');
    Row row13(1500 * multiplier, Direction::LEFT);
    row13.add(g131);


    //Construction de level 5
    Level level;
    level.addRow(empty);
    level.addRow(row1);
    level.addRow(row2);
    level.addRow(row3);
    level.addRow(row4);
    level.addRow(empty);
    level.addRow(row5);
    level.addRow(row6);
    level.addRow(empty);
    level.addRow(row7);
    level.addRow(empty);
    level.addRow(row8);
    level.addRow(empty);
    level.addRow(row9);
    level.addRow(row10);
    level.addRow(PowerUPRow());
    level.addRow(row11);
    level.addRow(row12);
    level.addRow(row13);
    level.addRow(empty);
    return level;
}
Level LevelsContructor::Level6()
{
    //Empty row (r�utilis�e plusieurs fois)
    Row empty(0, Direction::LEFT);

    //Row 1
    Hitbox h11 = Hitbox({ 0,1 }, TruckLeft(5));
    GameObject g11 = GameObject(h11, '@');
    Hitbox h12 = Hitbox({ 28,1 }, LimoLeft);
    GameObject g12 = GameObject(h12, '@');
    Row row1(1100 * multiplier, Direction::LEFT);
    Hitbox h13 = Hitbox({ 15,1 }, LimoRight);
    GameObject g13 = GameObject(h13, '@');
    row1.add(g11);
    row1.add(g12);
    row1.add(g13);

    //Row 2
    Hitbox h21 = Hitbox({ 20,17 }, TruckLeft(5));
    GameObject g21 = GameObject(h21, '@');
    Row row2(1200 * multiplier, Direction::LEFT);
    row2.add(g21);

    //Row 3
    Hitbox h31 = Hitbox({ WIDTH / 2,3 }, LimoRight);
    GameObject g31 = GameObject(h31, '@');
    Row row3(900 * multiplier, Direction::RIGHT);
    row3.add(g31);

    //Row 4
    Hitbox h41 = Hitbox({ WIDTH / 2,5 }, TruckRight(12));
    GameObject g41 = GameObject(h41, '@');
    Row row4(1300 * multiplier, Direction::RIGHT);
    row4.add(g41);

    //Row 5
    Hitbox h51 = Hitbox({ WIDTH / 2,7 }, TruckLeft(7));
    GameObject g51 = GameObject(h51, '@');
    Row row5(1300 * multiplier, Direction::LEFT);
    Hitbox h52 = Hitbox({ 0,7 }, LimoLeft);
    GameObject g52 = GameObject(h52, '@');
    row5.add(g51);
    row5.add(g52);

    //Row 6
    Hitbox h61 = Hitbox({ WIDTH / 2,9 }, TruckLeft(4));
    GameObject g61 = GameObject(h61, '@');
    Row row6(900 * multiplier, Direction::LEFT);
    row6.add(g61);

    //Row 7
    Hitbox h71 = Hitbox({ 0,11 }, TruckRight(7));
    GameObject g71 = GameObject(h71, '@');
    Hitbox h72 = Hitbox({ 16,11 }, TruckRight(7));
    GameObject g72 = GameObject(h72, '@');
    Hitbox h73 = Hitbox({ 32,11 }, LimoRight);
    GameObject g73 = GameObject(h73, '@');
    Row row7(1300 * multiplier, Direction::RIGHT);
    row7.add(g71);
    row7.add(g72);
    row7.add(g73);

    //Row 8
    Hitbox h81 = Hitbox({ WIDTH / 2,13 }, TruckLeft(8));
    GameObject g81 = GameObject(h81, '@');
    Hitbox h82 = Hitbox({0,13 }, TruckLeft(8));
    GameObject g82 = GameObject(h82, '@');
    Row row8(1100 * multiplier, Direction::LEFT);
    row8.add(g81);
    row8.add(g82);

    //Row 9
    Hitbox h91 = Hitbox({ WIDTH / 2,15 }, TruckRight(10));
    GameObject g91 = GameObject(h91, '@');
    Row row9(1200 * multiplier, Direction::RIGHT);
    row9.add(g91);

    //Row 10
    Hitbox h101 = Hitbox({ 1,17 }, TruckLeft(5));
    GameObject g101 = GameObject(h101, '@');
    Hitbox h102 = Hitbox({ 24,17 }, TruckLeft(8));
    GameObject g102 = GameObject(h102, '@');
    Row row10(900 * multiplier, Direction::LEFT);
    row10.add(g101);
    row10.add(g102);

    //Row 11
    Hitbox h111 = Hitbox({ 10,17 }, AutoLeft);
    GameObject g111 = GameObject(h111, '@');
    Row row11(1300 * multiplier, Direction::LEFT);
    row11.add(g111);

    //Row 12
    Hitbox h121 = Hitbox({ 20,17 }, LimoLeft);
    GameObject g121 = GameObject(h121, '@');
    Hitbox h122 = Hitbox({ 0,17 }, LimoLeft);
    GameObject g122 = GameObject(h122, '@');
    Row row12(1100 * multiplier, Direction::LEFT);
    row12.add(g121);
    row12.add(g122);

    //Row 13
    Hitbox h131 = Hitbox({ 20,17 }, TruckLeft(5));
    GameObject g131 = GameObject(h131, '@');
    Row row13(1300 * multiplier, Direction::LEFT);
    row13.add(g131);


    //Construction de level 6
    Level level;
    level.addRow(empty);
    level.addRow(row1);
    level.addRow(row2);
    level.addRow(row3);
    level.addRow(row4);
    level.addRow(empty);
    level.addRow(row5);
    level.addRow(row6);
    level.addRow(empty);
    level.addRow(row7);
    level.addRow(empty);
    level.addRow(row8);
    level.addRow(empty);
    level.addRow(row9);
    level.addRow(row10);
    level.addRow(empty);
    level.addRow(row11);
    level.addRow(row12);
    level.addRow(row13);
    level.addRow(empty);
    return level;
}