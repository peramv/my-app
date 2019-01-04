﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_no_joint_entity_record_available : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_no_joint_entity_record_available() { }
		~CIFast_Infrastructure_ifastdbrkr_err_no_joint_entity_record_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_JOINT_ENTITY_RECORD_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Can't init view thread.  Error: %error%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Can't init view thread.  Error: %error%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ansicht-Strang kann nicht gestartet werden.  Fehler: %error%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede iniciar la secuencia de view.  Error: %error%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'initier le fil de l'affichage. Erreur : %error%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("View-thread kan niet worden geïnitialiseerd.  Fout: %error%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



