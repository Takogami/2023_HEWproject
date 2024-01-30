#include "CEase.h"

void CEase::Init(float* start, float end, float dur, int delay, EASE ease)
{
	startPos = start;
	startData = *startPos;
	endPos = end;
	duration = dur * 60;
	startTime = delay * 60;
	count = 0;
	state = STATE::WAIT;

	auto Find = EaseDictionary.find(ease);
	if (Find != EaseDictionary.end())
	{
		Easeing = Find->second;
	}
	else
	{
		Easeing = &easeInSine;
	}
}

void CEase::Update()
{
	switch (state)
	{
	case STATE::WAIT:
		//�J�n�܂�
		if (count > startTime)
		{
			count = 0;
			state = STATE::UPDATE;
		}
		break;

	case STATE::UPDATE:
		//���ψ�
		if (count > duration)
		{
			state = STATE::END;
		}
		else
		{
			double r = count / duration;
			r = Easeing(r);
			// double�^��float�^�ɕϊ����ĕԂ�
			*startPos = (float)(startData+ (endPos - startData) * r);
		}
		break;

	case STATE::END:
		break;

	default:
		break;
	}

	count++;
}

STATE CEase::GetState()
{
	return state;
}
