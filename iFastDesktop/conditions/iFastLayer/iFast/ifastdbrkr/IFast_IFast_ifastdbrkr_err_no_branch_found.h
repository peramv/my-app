#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_branch_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_branch_found() { }
		~CIFast_IFast_ifastdbrkr_err_no_branch_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_BRANCH_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Branch is found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucun supérieur hiérarchique exist avec les co-ordonnées que vous avez spécifié.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Filiale gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha encontrado una sucursal")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune unité de service n'a été trouvée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen filiaal gevonden")); }

        // Actions
	};
}



