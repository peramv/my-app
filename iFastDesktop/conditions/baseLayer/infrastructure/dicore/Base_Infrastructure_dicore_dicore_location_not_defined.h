﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicore_dicore_location_not_defined : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicore_dicore_location_not_defined() { }
		~CBase_Infrastructure_dicore_dicore_location_not_defined() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_LOCATION_NOT_DEFINED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Persistent location not defined!")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Persistent location not defined!")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Fortdauernder Speicherort ist nicht definiert!")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. ¡No se ha definido la ubicación persistente!")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Lieu de persistance non défini!")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Vaste locatie is niet gedefinieerd!")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative to verify install configuration.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a support representative to verify install configuration.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter, um die Installationskonfiguration zu überprüfen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative to verify install configuration.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique pour vérifier la configuration de l'installation.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker om de installatieconfiguratie te controleren")); }
	};
}



