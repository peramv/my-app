#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_view : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_view() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_view() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_VIEW")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  Invalid attempt to use CBO for field %FIELD%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  Invalid attempt to use CBO for field %FIELD%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.  Das Objekt ist nicht initialisiert..")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  Intento no válido de utilizar CBO para el campo %FIELD%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Tentative invalide d'utilisation de l'optimisation de coûts pour le champ %FIELD%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Ongeldige poging om CBO te gebruiken voor veld %FIELD%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie, ob das Objekt initialisiert wurde.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht.")); }
	};
}



