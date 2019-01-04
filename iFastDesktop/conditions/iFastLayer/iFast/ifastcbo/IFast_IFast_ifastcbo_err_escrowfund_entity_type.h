#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_escrowfund_entity_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_escrowfund_entity_type() { }
		~CIFast_IFast_ifastcbo_err_escrowfund_entity_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ESCROWFUND_ENTITY_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This fund/class can only exist for entity type \"Escrow Representative\" or \"Assignee\" .")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Escrow fund class can only exist for entity type Escrow Representative.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Escrow-Fondsklasse darf nur für den Objekttyp Escrow-Repräsentant existieren.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La clase de fondo de custodia sólo puede existir para el tipo de entidad Representante de custodia")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce fonds/cette classe ne peut exister que pour l'entité de type Cessionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondscategorie Pand kan alleen bestaan voor eenheidstype Pandvertegenwoordiger")); }

        // Actions
	};
}



