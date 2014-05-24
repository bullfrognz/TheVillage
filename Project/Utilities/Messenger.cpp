//
//  Bryce Booth
//  Auckland
//  New Zealand
//
//  File Name :   Subject.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <map>
#include <vector>
#include <assert.h>


// Local Includes
#include "Framework\Observer.h"


// This Include
#include "Messenger.h"


// Static Variables


// Implementation


namespace Messenger
{
	std::map<uint, std::vector<IObserver*>> SubjectObservers;


	bool
	RegisterObserver(uint _uiSubjectId, IObserver* _pObserver)
	{
		std::map<uint, std::vector<IObserver*>>::iterator ObserversContainer;
		bool bReturn = true;


		ObserversContainer = SubjectObservers.find(_uiSubjectId);


		// Subject not registered
		if (ObserversContainer == SubjectObservers.end())
		{
			std::vector<IObserver*> TmpVector;
			TmpVector.push_back(_pObserver);


			SubjectObservers.insert( std::pair<uint, std::vector<IObserver*>>(_uiSubjectId, TmpVector) );


			ObserversContainer = SubjectObservers.find(_uiSubjectId);
		}
		else
		{
			(*ObserversContainer).second.push_back(_pObserver);
		}


		return (bReturn);
	}


	bool
	UnregisterObserver(uint _uiSubjectId, IObserver* _pObserver)
	{
		std::map<uint, std::vector<IObserver*>>::iterator ObserversContainer;
		bool bReturn = true;


		ObserversContainer = SubjectObservers.find(_uiSubjectId);


		std::vector<IObserver*>& rObservers = (*ObserversContainer).second;


		std::vector<IObserver*>::iterator CurrentObserver = rObservers.begin();
		std::vector<IObserver*>::iterator EndObserver = rObservers.end();


		for (CurrentObserver; CurrentObserver != EndObserver; ++ CurrentObserver)
		{
			if ((*CurrentObserver) == _pObserver)
			{
				rObservers.erase(CurrentObserver);


				break;
			}
		}


		return (bReturn);
	}


	bool
	Send(uint _uiSubjectId, void* _pData)
	{
		std::map<uint, std::vector<IObserver*>>::iterator ObserversContainer;
		bool bReturn = true;


		ObserversContainer = SubjectObservers.find(_uiSubjectId);


		if (ObserversContainer == SubjectObservers.end())
		{
			// Subject not found
			bReturn = false;
		}
		else
		{
			std::vector<IObserver*>& rObservers = (*ObserversContainer).second;


			std::vector<IObserver*>::iterator CurrentObserver = rObservers.begin();
			std::vector<IObserver*>::iterator EndObserver = rObservers.end();


			for (CurrentObserver; CurrentObserver != EndObserver; ++ CurrentObserver)
			{
				(*CurrentObserver)->NotifyMessage(_uiSubjectId, _pData);
			}
		}


		return (bReturn);
	}
};
