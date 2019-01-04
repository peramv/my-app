#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entity_type_escrow_not_permit : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entity_type_escrow_not_permit() { }
		~CIFast_IFast_ifastcbo_err_entity_type_escrow_not_permit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTITY_TYPE_ESCROW_NOT_PERMIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User has no permission on escrow entity maintenance.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzer hat keine Erlaubnis für Escrow-Objektpflege")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El usuario no tiene autorización sobre el mantenimiento de la entidad de custodia")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur n'est pas autorisé à effectuer la maintenance du cessionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("gebruiker is niet gemachtigd voor onderhoud pandeenheid")); }

        // Actions
	};
}



