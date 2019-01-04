﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_diawd23_diawd23_init_com_fail : public CConditionObject
	{
	public:
		CIFast_IFast_diawd23_diawd23_init_com_fail() { }
		~CIFast_IFast_diawd23_diawd23_init_com_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_INIT_COM_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Server was not able to perform the action %action% for the service %service%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Server was not able to perform the action %action% for the service %service%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Server konnte die Aktion %action%  für den Service %service% nicht ausführen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El servidor no pudo realizar la acción %action% para el servicio %service%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le serveur était incapable d'exécuter l'action %action% pour le service %service%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Server kon de actie %action% niet uitvoeren voor de dienst %service%")); }

        // Actions
	};
}



