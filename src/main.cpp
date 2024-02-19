#include "gladiator.h"
#include "../includes/main.h"

Gladiator* gladiator;
//int	id = gladiator->robot->getData().teamId;


size_t 	get_line_left(posmap *posmap);

Position posmid = {1.5, 1.5};

int	i = 0;
void reset();

void	stop(Gladiator *gladiator)
{
	gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.1f);
	gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.1f);
}


/**
 * @brief Cette fonction vérifie les quatre directions cardinales autour du robot pour voir si la case adjacente est accessible ou non.
 * @param {t_dir} dir
 * @returns {true}
*/
bool ok_dir(t_dir dir, Gladiator *gladiator)
{
	if (dir == nord && gladiator->maze->getNearestSquare()->northSquare)
	{
		stop(gladiator);
		return (true);
	}
	else if (dir == sud && gladiator->maze->getNearestSquare()->southSquare)
	{
		stop(gladiator);
		return (true);
	}
	else if (dir == est && gladiator->maze->getNearestSquare()->eastSquare)
	{
		stop(gladiator);
		return (true);
	}
	else if (dir == ouest && gladiator->maze->getNearestSquare()->westSquare)
	{
		stop(gladiator);
		return (true);
	}
	return (false);
}

/**
 * Calcule le plus long chemin en ligne droite vers le `Nord`.
*/
size_t 	get_line_up(posmap *posmap)
{
	size_t i = 0;
	size_t cmp = 0;

	while (gladiator->maze->getSquare(posmap->i , posmap->j + i)->northSquare)
	{
		if (!(gladiator->maze->getSquare(posmap->i + i, posmap->j)->possession == 2))
			cmp++;
		i++;
	}
	return (cmp);
}

/**
 * Calcule le plus long chemin en ligne droite vers le `Sud`.
*/
size_t 	get_line_down(posmap *posmap)
{
	size_t i = 0;
	size_t cmp = 0;

	while (gladiator->maze->getSquare(posmap->i, posmap->j - i)->southSquare)
	{
		if (!(gladiator->maze->getSquare(posmap->i + i, posmap->j)->possession == 2))
			cmp++;
		i++;
	}
	return (cmp);
}

/**
 * Calcule le plus long chemin en ligne droite vers l'`Ouest`.
 * @param {posmap}.
 * Variables:
 * - `(size_t) i`: .
 * - `(size_t) cmp`: .
 * @returns `(size_t) cmp`: . 
*/
size_t 	get_line_left(posmap *posmap)
{
	size_t i = 0;
	size_t cmp = 0;

	while (gladiator->maze->getSquare(posmap->i - i, posmap->j)->westSquare)
	{
		if (!(gladiator->maze->getSquare(posmap->i + i, posmap->j)->possession == 2))
			cmp++;
		i++;
	}
	return (cmp);
}

/**
 * Calcule le plus long chemin en ligne droite vers l'`Est`.
*/
size_t 	get_line_right(posmap *posmap)
{
	size_t i = 0;
	size_t	cmp = 0;
	while (gladiator->maze->getSquare(posmap->i + i, posmap->j)->eastSquare) 
	{
		if (!(gladiator->maze->getSquare(posmap->i + i, posmap->j)->possession == 2))
			cmp++;
			
		i++;
	}
	return (cmp);
}

/**
 * 
*/
bool cote_line(Gladiator *gladiator, posmap *posmap)
{
	size_t max_nord = get_line_up(posmap);
	size_t max_sud = get_line_down(posmap);
	size_t max_est = get_line_right(posmap);
	size_t max_ouest = get_line_left(posmap);

	if (max_nord > 1 && max_nord > max_sud && max_nord > max_est && max_nord > max_ouest)
	{
		posmap->next_move = nord;
		return (false);
	}
	else if (max_sud > 1 && max_sud > max_nord && max_sud > max_est && max_sud > max_ouest)
	{
		posmap->next_move = sud;
		return (false);
	}
	else if (max_est > 1 && max_est > max_nord && max_est > max_sud && max_est > max_ouest)
	{
		posmap->next_move = est;
		return (false);
	}
	else if (max_ouest > 1 && max_ouest > max_nord && max_ouest > max_sud && max_ouest > max_est)
	{
		posmap->next_move = ouest;
		return (false);
	}
	return (true);
}

bool cote_steal(Gladiator *gladiator, posmap *posmap)
{
	if (posmap->j < 12 - posmap->border && ok_dir(nord, gladiator) && gladiator->maze->getSquare(posmap->i, posmap->j + 1)->possession == 2)
	{
		posmap->next_move = nord;
		return (false);
	}
	else if (posmap->j > 0 + posmap->border && ok_dir(sud, gladiator) && gladiator->maze->getSquare(posmap->i, posmap->j - 1)->possession == 2)
	{
		posmap->next_move = sud;
		return (false); 
	}    
	else if (posmap->i < 12 - posmap->border && ok_dir(est, gladiator) && gladiator->maze->getSquare(posmap->i + 1, posmap->j)->possession == 2)
	{
		posmap->next_move = est;
		return (false);
	}
	else if (posmap->i > 0 + posmap->border && ok_dir(ouest, gladiator) && gladiator->maze->getSquare(posmap->i - 1, posmap->j)->possession == 2)
	{
		posmap->next_move = ouest;
		return (false);
	}
	return (true);
}

bool cote_empty(Gladiator *gladiator, posmap *posmap)
{
	if (posmap->j < 12  - posmap->border && ok_dir(nord, gladiator) && gladiator->maze->getSquare(posmap->i, posmap->j + 1)->possession == 0)
	{
		posmap->next_move = nord;
		return (false);
	}
	else if (posmap->j > 0  + posmap->border && ok_dir(sud, gladiator) && gladiator->maze->getSquare(posmap->i, posmap->j - 1)->possession == 0)
	{
		posmap->next_move = sud;
		return (false); 
	}    
	else if (posmap->i < 12  - posmap->border && ok_dir(est, gladiator) && gladiator->maze->getSquare(posmap->i + 1, posmap->j)->possession == 0)
	{
		posmap->next_move = est;
		return (false);
	}
	else if (posmap->i > 0  + posmap->border && ok_dir(ouest, gladiator) && gladiator->maze->getSquare(posmap->i - 1, posmap->j)->possession == 0)
	{
		posmap->next_move = ouest;
		return (false);
	}
	return (true);
}


bool cote_useless(Gladiator *gladiator, posmap *posmap)
{
	if (posmap->j < 12 - posmap->border && ok_dir(nord, gladiator) && gladiator->maze->getSquare(posmap->i, posmap->j + 1)->possession == 1)
	{
		posmap->next_move = nord;
		return (false);
	}
	else if (posmap->j > 0 + posmap->border && ok_dir(sud, gladiator) && gladiator->maze->getSquare(posmap->i, posmap->j - 1)->possession == 1)
	{
		posmap->next_move = sud;
		return (false); 
	}    
	else if (posmap->i < 12 - posmap->border && ok_dir(est, gladiator) && gladiator->maze->getSquare(posmap->i + 1, posmap->j)->possession == 1)
	{
		posmap->next_move = est;
		return (false);
	}
	else if (posmap->i > 0 + posmap->border && ok_dir(ouest, gladiator) && gladiator->maze->getSquare(posmap->i - 1, posmap->j)->possession == 1)
	{
		posmap->next_move = ouest;
		return (false);
	}
	return (true);
}

float kw = 9.f;
float kv = 1.30f;
float wlimit = 3.f;
float vlimit = 0.6;
float erreurPos = 0.07;

double reductionAngle(double x)
{
	x = fmod(x + PI, 2 * PI);
	if (x < 0)
		x += 2 * PI;
	return x - PI;
}

void go_to(Position cons, Position pos)
{
	double consvl, consvr;
	double dx = cons.x - pos.x;
	double dy = cons.y - pos.y;
	double d = sqrt(dx * dx + dy * dy);

	if (d > erreurPos)
	{
		double rho = atan2(dy, dx);
		double consw = kw * reductionAngle(rho - pos.a);

		double consv = kv * d * cos(reductionAngle(rho - pos.a));
		consw = abs(consw) > wlimit ? (consw > 0 ? 1 : -1) * wlimit : consw;
		consv = abs(consv) > vlimit ? (consv > 0 ? 1 : -1) * vlimit : consv;

		consvl = consv - gladiator->robot->getRobotRadius() * consw; // GFA 3.6.2
		consvr = consv + gladiator->robot->getRobotRadius() * consw; // GFA 3.6.2
	}
	else
	{
		consvr = 0;
		consvl = 0;
	}
	gladiator->control->setWheelSpeed(WheelAxis::RIGHT, consvr , false); // GFA 3.2.1
	gladiator->control->setWheelSpeed(WheelAxis::LEFT, consvl, false);  // GFA 3.2.1
}

/**
 * Fonction de reset.
*/
void reset()
{
	gladiator->log("Call of reset function"); // GFA 4.5.1
}

float	inttopos(int i)
{
	return (i * 0.25);
}

int	postoint(float i)
{
	return static_cast<int>(floor(i / 0.25));
}

posmap	choosedir(t_dir dir, posmap pos)
{
	posmap map = {0, 0};
	switch (dir)
	{
	case nord:
		map.j += 1;
		break;
	case sud:
		map.j -= 1;
		break;
	case est:
		map.i += 1;
		break;
	case ouest:
		map.i -= 1;
		break;
	}
	return (map);
}

void	dep(Position myPosition, posmap dir)
{
	Position goal {myPosition.x + inttopos(dir.i), myPosition.y + inttopos(dir.j), 0};
	if (((postoint(myPosition.x) != postoint(goal.x)) || (postoint(myPosition.y) != postoint(goal.y))))
	{
		go_to(goal, myPosition);
		delay(50);
	}
}

void best_decision(Gladiator *gladiator)
{
	posmap posmap = {gladiator->maze->getNearestSquare()->i, gladiator->maze->getNearestSquare()->j};
	if (i == 0)
	{
		posmap = {.border = 0};
		i++;
	}
	if (cote_steal(gladiator, &posmap))
	{
		if(cote_empty(gladiator, &posmap))
			if(!cote_useless(gladiator, &posmap))
				dep(gladiator->robot->getData().position, choosedir(posmap.next_move, posmap));
		else
			dep(gladiator->robot->getData().position, choosedir(posmap.next_move, posmap));
	}
	else
		dep(gladiator->robot->getData().position, choosedir(posmap.next_move, posmap));
}

/**
 * Récupère le temps écoulé.
*/
clock_t gettime()
{
	return (clock() / (CLOCKS_PER_SEC / 1000));
}

/**
 * Fonction appelée au démarrage du robot
*/
void setup() {
	gladiator = new Gladiator();
	gladiator->game->onReset(&reset); // GFA 4.4.1
}

/**
 * Boucle de jeu
*/
void loop() {
	if(gladiator->game->isStarted())
		best_decision(gladiator);
	delay(10);
}