#pragma once
#ifndef OBJECT_H
#define OBJECT_H

class Object
{
private:

public:
	virtual void Start() {};
	virtual void Update() {};

	virtual ~Object() {};
};

#endif