#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_confirm_type_only_valid_for_swift : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_confirm_type_only_valid_for_swift() { }
		~CIFast_IFast_ifastcbo_err_confirm_type_only_valid_for_swift() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONFIRM_TYPE_ONLY_VALID_FOR_SWIFT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Other confirm type value is only valid for Swift Like  networks.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Other confirm type value is only valid for SWIFT networks.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de l'autre type de confirmation n'est valide que pour les réseaux de modèle Swift.")); }

        // Actions
	};
}



