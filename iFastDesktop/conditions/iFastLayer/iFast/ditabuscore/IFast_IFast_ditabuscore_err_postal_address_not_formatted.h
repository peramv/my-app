#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_postal_address_not_formatted : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_postal_address_not_formatted() { }
		~CIFast_IFast_ditabuscore_err_postal_address_not_formatted() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_POSTAL_ADDRESS_NOT_FORMATTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No search criteria could be found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Impossible de trouver des criteres de recherche.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es konnten keine Suchkriterien gefunden werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No pudieron encontrarse criterios de búsqueda.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun critère de recherche n'a pu être trouvé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen zoekcriteria gevonden")); }

        // Actions
	};
}



