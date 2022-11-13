//Spawn helper function
void SpawnObject(string type, vector position, vector orientation)
{
	auto obj = GetGame () .CreateObject ( type, position );
	obj.SetPosition( position );
	obj.SetOrientation( orientation );
	obj.SetOrientation( obj.GetOrientation() ); //Collision fix
	obj.Update();
	obj.SetAffectPathgraph( true, false );
	if(obj.CanAffectPathgraph() ) GetGame().GetCallQueue ( CALL_CATEGORY_SYSTEM ).CallLater( GetGame().UpdatePathgraphRegionByObject, 100, false, obj );
}

void main()
{
	
	SpawnObject( "Land_Tank_Big", "2321.080078 15.547000 5720.290039", "-2.728735 0.000000 0.000000" );
	SpawnObject( "Land_Tank_Big", "2335.209961 15.700500 5708.279785", "-54.119553 0.000000 0.000000" );
	SpawnObject( "Land_Workshop5", "2352.050049 13.283800 5695.140137", "-47.668228 0.000000 0.000000" );
	SpawnObject( "Land_Workshop3", "2365.260010 13.885200 5704.229980", "41.237335 0.000000 -0.000000" );
	SpawnObject( "vbldr_tower_tc4_base", "2413.830078 34.546600 5691.529785", "0.000000 0.000000 -0.000000" );
	SpawnObject( "vbldr_tower_tc4_mid", "2414.030029 77.932503 5691.589844", "0.000000 0.000000 -0.000000" );
	SpawnObject( "vbldr_tower_tc4_top", "2413.949951 118.468002 5691.750000", "0.031474 0.000000 -0.000000" );
	SpawnObject( "Land_Misc_Well_Pump_Yellow", "2354.969971 12.826500 5706.689941", "-11.891246 0.000000 0.000000" );
	SpawnObject( "Land_Workshop_FuelStation", "2357.340088 16.450600 5800.649902", "-129.993866 0.000000 -0.000000" );
	SpawnObject( "Land_Water_Station", "2428.110107 18.580400 5757.799805", "48.927696 0.000000 0.000000" );
	SpawnObject( "Land_Container_1Mo", "2340.879883 16.822300 5781.729980", "46.828503 0.000000 -0.000000" );
	SpawnObject( "Land_Container_1Bo", "2350.080078 15.797500 5803.250000", "50.289913 0.000000 -0.000000" );
	SpawnObject( "Land_Container_1Mo", "2353.270020 19.911301 5797.109863", "-39.824776 0.000000 0.000000" );
	SpawnObject( "Land_Container_1Bo", "2356.100098 20.073700 5799.609863", "-39.014465 0.000000 0.000000" );
	SpawnObject( "Land_Shed_W5", "2389.229980 16.543600 5745.180176", "42.766792 0.000000 0.000000" );
	SpawnObject( "Land_House_1W01", "2383.689941 18.704599 5756.899902", "41.652550 0.000000 -0.000000" );
	SpawnObject( "Land_Garage_Small", "2383.679932 16.206499 5741.399902", "131.245453 0.000000 -0.000000" );
	SpawnObject( "Land_House_1W05_Yellow", "2535.492432 22.243465 5694.161621", "90.000000 0.000000 0.000000" );
	SpawnObject( "Land_Garage_Small", "2548.563232 20.402317 5691.125000", "-179.999893 0.000000 0.000000" );
	SpawnObject( "Land_Shed_W5", "2555.322266 21.374807 5697.611816", "0.000000 0.000000 0.000000" );
	SpawnObject( "Land_Wreck_S1023_Blue", "2552.770996 20.861599 5701.348145", "45.000000 0.000000 0.000000" );
	SpawnObject( "Land_Wreck_Volha_Grey", "2536.090332 20.058062 5704.324707", "64.999992 0.000000 0.000000" );
	SpawnObject( "Land_Wreck_Lada_Red", "2548.580566 20.362734 5698.943359", "15.000000 0.000000 0.000000" );
	SpawnObject( "Land_Wreck_sed01_aban1_white", "2557.979492 20.720480 5702.816895", "76.999809 0.000000 0.000000" );
	SpawnObject( "Wreck_mi8_Crashed", "2545.854736 16.719635 5603.579590", "0.000000 0.000000 0.000000" );	
	SpawnObject( "Land_House_1W03", "2288.399902 14.000000 6238.250000", "-0.000000 0.000000 0.000000" );
	

	/*
	  [Namalsk] CE init (offline)
	*/
	CreateHive();
	GetHive().InitOffline();
	// redo eco pos
	//GetCEApi().ExportProxyData( "10240 0 10240", 20480 );  //Center of map, radius of how far to go out and find building
	// remove comment to regen after adding buildings

	/*
	  [Namalsk] Mission time init
	   after CE init to determine if storage mission type is outside of the required time-frame
	   currently recommended time-frame is:
		11/1 -> 11/30
		keep in mind that gameplay features are tied to the mission date (stored in the storage) and that it SHOULD remain this period!
	   while using:
		day accelerated 6 times (serverTimeAcceleration=6), resulting in an average 78 min of day-time (RL)
		night accelerated 24 times (serverNightTimeAcceleration=4), resulting in an average of 26 min of night-time (RL)
	*/
	int year, month, day, hour, minute;
	GetGame().GetWorld().GetDate( year, month, day, hour, minute );

    if ( ( month < 11 ) || ( month >= 12 ) )
    {
    	year = 2011;
        month = 11;
        day = 1;
		
		GetGame().GetWorld().SetDate( year, month, day, hour, minute );
	}
};

class CustomMission: MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		// this piece of code is recommended otherwise event system is switched on automatically and runs from default values
		// comment this whole block if NOT using Namalsk Survival
		if ( m_EventManagerServer )
		{
			// enable/disable event system, min time between events, max time between events, max number of events at the same time
			m_EventManagerServer.OnInitServer( true, 550, 1000, 2 );
			// registering events and their probability
			m_EventManagerServer.RegisterEvent( Aurora, 0.85 );
			m_EventManagerServer.RegisterEvent( Blizzard, 0.4 );
			m_EventManagerServer.RegisterEvent( ExtremeCold, 0.4 );
			m_EventManagerServer.RegisterEvent( Snowfall, 0.6 );
			m_EventManagerServer.RegisterEvent( EVRStorm, 0.35 );
			m_EventManagerServer.RegisterEvent( HeavyFog, 0.3 );
		}
	}

	void SetRandomHealth(EntityAI itemEnt)
	{
		if (itemEnt)
		{
			float rndHlt = Math.RandomFloat( 0.50, 0.85 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override void StartingEquipSetup( PlayerBase player, bool clothesChosen )
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;
		
		// top
		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );

			itemEnt = itemClothing.GetInventory().CreateInInventory( "Rag" );
			if ( Class.CastTo( itemBs, itemEnt ) )
			{
				SetRandomHealth( itemEnt );
				itemBs.SetQuantity( 4 );
				itemBs.SetCleanness( 1 );
			}
			player.SetQuickBarEntityShortcut( itemEnt, 0 );
			
			itemEnt = itemClothing.GetInventory().CreateInInventory( "RoadFlare" );
			SetRandomHealth( itemEnt );
			itemEnt = itemClothing.GetInventory().CreateInInventory( "RoadFlare" );
			SetRandomHealth( itemEnt );
			player.SetQuickBarEntityShortcut( itemEnt, 1 );
		}

		// pants
		itemClothing = player.FindAttachmentBySlotName( "Legs" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );

			itemEnt = itemClothing.GetInventory().CreateInInventory( "Heatpack" );
			SetRandomHealth( itemEnt );

			int throwDice = Math.RandomInt( 0, 2 );
			if ( throwDice == 0 )
				itemEnt = itemClothing.GetInventory().CreateInInventory( "dzn_tool_watch" );
			else
				itemEnt = itemClothing.GetInventory().CreateInInventory( "dzn_tool_watch2" );
			player.SetQuickBarEntityShortcut( itemEnt, 2 );
		}

		// shoes
		itemClothing = player.FindAttachmentBySlotName( "Feet" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );
		}

		// bump fresh spawn water and energy values (to compensate for the frozen food and harder-to-get wells)
		player.GetStatWater().Set( 900 );
		player.GetStatEnergy().Set( 1100 );
	}
};
  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
};
