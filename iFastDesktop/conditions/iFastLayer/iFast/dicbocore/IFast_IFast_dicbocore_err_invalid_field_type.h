#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_invalid_field_type : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_invalid_field_type() { }
		~CIFast_IFast_dicbocore_err_invalid_field_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FIELD_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Automatic transfers may not be set up for an Escrow/Assignee account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Automatic transfers may not be set up for an Escrow account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Automatische Transfers können für ein Escrow-(Ander)konto nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No pueden configurarse transferencias automáticas para una cuenta de custodia.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les transferts automatiques ne doivent pas être réglés pour un compte cédé en garantie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Automatische overdrachten kunnen niet worden ingesteld voor een pandaccount")); }

        // Actions
	};
}



