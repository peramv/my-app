#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_sin_different_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_sin_different_entity() { }
		~CIFast_IFast_ifastcbo_err_duplicate_sin_different_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_SIN_DIFFERENT_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate SIN found in the entity list.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Doppelte SIN in der Objektliste gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se encontró un SIN repetido en la lista de entidades.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une copie du NAS a été trouvée dans la liste d'entités.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dubbele SIN gevonden in eenhedenlijst")); }

        // Actions
	};
}



