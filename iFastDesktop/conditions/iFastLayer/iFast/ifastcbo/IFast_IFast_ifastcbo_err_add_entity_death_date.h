#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_add_entity_death_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_add_entity_death_date() { }
		~CIFast_IFast_ifastcbo_err_add_entity_death_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADD_ENTITY_DEATH_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The addition of a deceased entity is not permitted.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'ajout d'entite decedee n'est pas autorisé.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Hinzufügen eines nicht mehr existierenden Objekts ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite añadir una entidad que ha dejado de operar.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'ajout d'une entité décédée n'est pas autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toevoegen van een overleden eenheid is niet toegestaan")); }

        // Actions
	};
}



