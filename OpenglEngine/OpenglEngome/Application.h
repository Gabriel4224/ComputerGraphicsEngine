#pragma once
class Application
{
public:

	virtual void Update(); 
	virtual void StartUp() = 0;
	virtual void ShutDown() = 0;

};

