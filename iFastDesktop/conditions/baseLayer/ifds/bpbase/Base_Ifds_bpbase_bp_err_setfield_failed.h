﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bpbase_bp_err_setfield_failed : public CConditionObject
	{
	public:
		CBase_Ifds_bpbase_bp_err_setfield_failed() { }
		~CBase_Ifds_bpbase_bp_err_setfield_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_SETFIELD_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  Set field failed for field %FIELD%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  Set field failed for field %FIELD%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Maximale Anzahl von laufenden Sitzungen wird überschritten")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  Falló Definir campo para el campo %FIELD%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Échec de réglage de champ pour le champ %FIELD%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Veld instellen is mislukt voor veld %FIELD%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht.")); }
	};
}



