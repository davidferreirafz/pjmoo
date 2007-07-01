#ifndef PARTICLESYSTEMFOGOSARTIFICIO_H
#define PARTICLESYSTEMFOGOSARTIFICIO_H

#include "ParticleSystem.h"


class ParticleSystemFogosArtificio : public ParticleSystem
{
public:
	ParticleSystemFogosArtificio();
	~ParticleSystemFogosArtificio();
	void criar();
	void atualizar();
};

#endif 
