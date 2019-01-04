#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_bp_err_no_search_crtiteria : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_bp_err_no_search_crtiteria() { }
		~CIFast_Infrastructure_ifastcbo_bp_err_no_search_crtiteria() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_NO_SEARCH_CRTITERIA")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Zip code cannot be set for an unformatted address.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Zip code cannot be set for an unformatted address.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Postleitzahl kann nicht für eine unformatierte Adresse festgelegt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede definir el código postal para una dirección no formateada.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code postal ne peut être réglé pour une adresse qui n'est pas mise en forme.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Postcode kan niet worden ingesteld voor een niet-ingedeeld adres")); }

        // Actions
	};
}



