#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_group_code_level : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_group_code_level() { }
		~CIFast_IFast_ifastcbo_err_group_code_level() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GROUP_CODE_LEVEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Group code level not set for this management company.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le niveau de code de groupe n'est pas defini pour cette societe de gestion")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Gruppencode-Level für dieses Management-Unternehmen ist nicht festgelegt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha definido el nivel de código de grupo para esta compañía administradora")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le niveau du code de groupe n'est pas réglé pour cet environnement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Groepscodeniveau is niet ingesteld voor dit beheerbedrijf")); }

        // Actions
	};
}



