#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_already_signed_on : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_already_signed_on() { }
		~CIFast_IFast_dita2kdb_dita2kdb_already_signed_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_ALREADY_SIGNED_ON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Search criteria field is empty.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Les criteres de recherche sont vides !")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Suchkriterien werden nicht ausgefüllt!")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los criterios de búsqueda están vacíos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Critère de recherche est vide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Zoekcriteria zijn niet ingevuld!")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please enter the %LABEL1%")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Veuillez saisir le %LABEL1%")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie %LABEL1% ein")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please enter the %LABEL1%")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez entrer l'étiquette %LABEL1%.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Geef het %LABEL1% op")); }
	};
}



