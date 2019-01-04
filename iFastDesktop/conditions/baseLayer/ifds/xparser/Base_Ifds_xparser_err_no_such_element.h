#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_xparser_err_no_such_element : public CConditionObject
	{
	public:
		CBase_Ifds_xparser_err_no_such_element() { }
		~CBase_Ifds_xparser_err_no_such_element() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_SUCH_ELEMENT")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No such element")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ungebundene Daten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un elemento de ese tipo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun élément")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Een dergelijk element bestaat niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check input data")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Bestätigen Sie die Daten und wiederholen Sie den Vorgang")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez les données saisies.")); }
	};
}



