#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_freq_diff_from_def : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_freq_diff_from_def() { }
		~CIFast_IFast_ifastcbo_err_freq_diff_from_def() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FREQ_DIFF_FROM_DEF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You have changed the system definition of %FREQUENCY%. This systematic will not run during months indicated with a 'N'.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Vous avez modifie la definition systeme de %FREQUENCY%. Cette methode de classification ne sera pas activee pour les mois indiques par N.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sie haben die Systemdefinition von %FREQUENCY% geändert. Dieser Systematische Plan läuft nicht während der mit \"N\" gekennzeichneten Monate.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ha modificado la definición del sistema de %FREQUENCY%. Este plan sistemático no se ejecutará durante los meses indicados con una 'N'.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous avez changé la définition du système de %FREQUENCY%. Cette systématique ne sera pas exécutée pendant les mois marqués d'un N.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("U hebt de systeemdefinitie van %FREQUENCY% gewijzigd. Dit systeemplan wordt niet uitgevoerd in maanden die zijn aangegeven met een 'N'")); }

        // Actions
	};
}



