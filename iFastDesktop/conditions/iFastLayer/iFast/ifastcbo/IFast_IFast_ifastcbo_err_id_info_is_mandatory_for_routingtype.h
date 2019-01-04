#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_id_info_is_mandatory_for_routingtype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_id_info_is_mandatory_for_routingtype() { }
		~CIFast_IFast_ifastcbo_err_id_info_is_mandatory_for_routingtype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ID_INFO_IS_MANDATORY_FOR_ROUTINGTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund broker ID information is mandatory for the selected routing type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund broker ID information is mandatory for the selected routing type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur le code de courtier en fonds est requise pour le type d'acheminement sélectionné.")); }

        // Actions
	};
}



