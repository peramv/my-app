#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warning_document_type_is_onhold : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warning_document_type_is_onhold() { }
		~CIFast_IFast_ifastcbo_warning_document_type_is_onhold() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARNING_DOCUMENT_TYPE_IS_ONHOLD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%DOCTYPE% is held at account (shareholder) level.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%DOCTYPE% wird auf Konto (Aktionärs-)-Ebene gehalten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%DOCTYPE% es mantenido a nivel de la cuenta (accionista).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de document %DOCTYPE% est détenu au niveau du compte (de l'actionnaire).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%DOCTYPE% wordt gehouden op accountniveau (aandeelhouder)")); }

        // Actions
	};
}



