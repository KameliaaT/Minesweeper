# Minesweeper
Minesweeper (Минер) е класическа еднопотребителска пъзел игра, в която целта на играча е да открие всички клетки в правоъгълна решетка, без да удари в мина. На игралната дъска първоначално се покриват клетките, някои от които могат да съдържат мина. Играчът може да извършва три вида действия: отваряне на клетка, маркиране на клетка като потенциална мина и отмаркиране на клетка. Играта предоставя подсказки във формата на числа, които показват броя на мините в съседство на дадена клетка.
Кода реализира играта "Minesweeper" в конзола. Вашата задача е да откриете всички безопасни клетки, без да стъпите на мина. Ето как работи кодът:

1.Стартиране на играта:

Преди да започнете играта, вие задавате размер на игралната дъска (между 3x3 и 10x10) и брой мини.
След това се генерират случайни местоположения на мините върху дъската.
Игрови интерфейс:

2.Всеки ход въвеждате команда ('o' за отваряне, 'm' за маркиране, 'u' за отмаркиране) и координати на клетка върху дъската.
Цел на играта:

3.Отваряте клетки с надеждата да не попаднете на мина.
Ако откриете мина, играта приключва и губите.
Печелите, когато успешно маркирате всички местоположения на мините.
Други функции:

4.Играта ви предоставя брой оставащи ходове.
Ако отворите клетка без мина, разкриват се и съседните безопасни клетки автоматично.
Край на играта:

5.Играта приключва, когато попаднете на мина или успешно маркирате всички мини.
След край на играта се показва крайното състояние на дъската.
