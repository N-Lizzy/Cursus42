#include "codexion.h"

int	try_take(t_dongle *dongle, long now, long cooldown)
{
	int	ok;

	pthread_mutex_lock(&dongle->dmutex);
	ok = (!dongle->is_taken && now - dongle->last_used >= cooldown);
	if (ok)
		dongle->is_taken = 1;
	pthread_mutex_unlock(&dongle->dmutex);
	return (ok);
}

void	give_back(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->dmutex);
	dongle->is_taken = 0;
	pthread_mutex_unlock(&dongle->dmutex);
}

int	take_dongles(t_coder *coder)
{
	t_hub	*hub;
	long	now;

	hub = coder->hub;
	now = get_time(hub->htime);
	if (!try_take(coder->left_dongle, now, hub->tcooldown))
		return (0);
	if (coder->left_dongle == coder->right_dongle)
		return (1);
	if (!try_take(coder->right_dongle, now, hub->tcooldown))
	{
		give_back(coder->left_dongle);
		return (0);
	}
	return (1);
}

int	release_dongles(t_coder *coder)
{
	t_hub	*hub;
	long	now;

	hub = coder->hub;
	now = get_time(hub->htime);
	pthread_mutex_lock(&coder->left_dongle->dmutex);
	coder->left_dongle->is_taken = 0;
	coder->left_dongle->last_used = now;
	pthread_mutex_unlock(&coder->left_dongle->dmutex);
	if (coder->right_dongle == coder->left_dongle)
		return (0);
	pthread_mutex_lock(&coder->right_dongle->dmutex);
	coder->right_dongle->is_taken = 0;
	coder->right_dongle->last_used = now;
	pthread_mutex_unlock(&coder->right_dongle->dmutex);
	return (0);
}