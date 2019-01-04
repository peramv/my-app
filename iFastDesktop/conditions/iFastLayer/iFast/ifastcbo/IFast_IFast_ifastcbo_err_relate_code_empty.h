#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_relate_code_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_relate_code_empty() { }
		~CIFast_IFast_ifastcbo_err_relate_code_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RELATE_CODE_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Relationship to owner cannot be empty.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Relationship to owner cannot be empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Beziehung zum Eigentümer muss eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El vínculo con el propietario no puede estar vacío.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Relation avec le propriétaire doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Relatie met eigenaar kan niet leeg zijn")); }

        // Actions
	};
}



