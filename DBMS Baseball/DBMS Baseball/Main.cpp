// DBMS Baseball.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Dbms.h"
#include "Entity.h"

using namespace std;

Dbms dbms;

void createTables();
void printStructDbms();
void inserData();
void select();
void selectCondition();
void printError();

int main()
{
	dbms = Dbms();

	createTables();

	//test
	printStructDbms();

	//insert
	inserData();

	//select *
	//select();

	//select condition
	//selectCondition();

	system("pause");

    return EXIT_SUCCESS;
}

void createTables() {
	//estadio
	Column estadioId = Column("estadioId", DataType::INTEGER, true);
	Column estadioNombre = Column("estadioNombre", DataType::VARCHAR, false);
	Column estatioFechaInaguracion = Column("estadioFechaInaguracion", DataType::DATE, false);

	vector<Column> estadioColumnas;
	estadioColumnas.push_back(estadioId);
	estadioColumnas.push_back(estadioNombre);
	estadioColumnas.push_back(estatioFechaInaguracion);

	Entity estadio = Entity("Estadio", estadioColumnas);

	//equipo
	Column equipoId = Column("equipoId", DataType::INTEGER, true);
	Column equipoNombre = Column("equipoNombre", DataType::VARCHAR, false);
	Column equipoFechaInaguracion = Column("equipoFechaInaguracion", DataType::DATE, false);
	Column equipoCantidadJuegadores = Column("equipoCantidadJuegadores", DataType::INTEGER, false);

	vector<Column> equipoColumnas;
	equipoColumnas.push_back(equipoId);
	equipoColumnas.push_back(equipoNombre);
	equipoColumnas.push_back(equipoFechaInaguracion);
	equipoColumnas.push_back(equipoCantidadJuegadores);

	Entity equipo = Entity("Equipo", equipoColumnas);

	//juego
	Column juegoId = Column("juegoId", DataType::INTEGER, true);
	Column juegoEstadioId = Column("estadioId", DataType::INTEGER, false);
	Column juegoFecha = Column("juegoFecha", DataType::DATE, false);
	Column equipoHome = Column("equipoHome", DataType::INTEGER, false);
	Column equipoVisitante = Column("equipoVisitante", DataType::INTEGER, false);

	vector<Column> juegoColumnas;
	juegoColumnas.push_back(juegoId);
	juegoColumnas.push_back(juegoEstadioId);
	juegoColumnas.push_back(juegoFecha);
	juegoColumnas.push_back(equipoHome);
	juegoColumnas.push_back(equipoVisitante);

	ForeignKey juegoEstadioFK = ForeignKey("Estadio","Juego","id","estadioId");
	ForeignKey juegoEquiHomeFK = ForeignKey("Equipo", "Juego", "id", "equipoHome");
	ForeignKey juegoEquiVisitanteFK = ForeignKey("Equipo", "Juego", "id", "equipoVisitante");

	vector<ForeignKey> juegoFKs;
	juegoFKs.push_back(juegoEstadioFK);
	juegoFKs.push_back(juegoEquiHomeFK);
	juegoFKs.push_back(juegoEquiVisitanteFK);
	
	Entity juego = Entity("Juego", juegoColumnas, juegoFKs);

	//entrada
	Column entradaId = Column("entradaId", DataType::INTEGER, true);
	Column descripcionEntrada = Column("descripcionEntrada", DataType::VARCHAR, false);
	Column entradaJuegoId = Column("entradaJuegoId", DataType::INTEGER, false);

	vector<Column> entradaColumnas;
	entradaColumnas.push_back(entradaId);
	entradaColumnas.push_back(descripcionEntrada);

	ForeignKey entradaJuegoFK = ForeignKey("Juego","Entrada","id","entradaJuegoId");

	vector<ForeignKey> entradaFks;
	entradaFks.push_back(entradaJuegoFK);

	Entity entrada = Entity("Entrada", entradaColumnas, entradaFks);

	//jugador
	Column juegadorId = Column("juegadorId", DataType::INTEGER, true);
	Column jugadorNombre = Column("jugadorNombre", DataType::VARCHAR, false);
	Column jugadorApellido = Column("jugadorApellido", DataType::VARCHAR, false);
	Column jugadorEdad = Column("jugadorEdad", DataType::INTEGER, false);
	Column jugadorEquipoId = Column("jugadorEquipoId", DataType::INTEGER, false);

	vector<Column> jugadorColumnas;
	jugadorColumnas.push_back(juegadorId);
	jugadorColumnas.push_back(jugadorNombre);
	jugadorColumnas.push_back(jugadorApellido);
	jugadorColumnas.push_back(jugadorEdad);
	jugadorColumnas.push_back(jugadorEquipoId);

	ForeignKey jugadorEquipoFK = ForeignKey("Equipo", "Jugador", "id", "jugadorEquipoId");

	vector<ForeignKey> jugadorFks;
	jugadorFks.push_back(jugadorEquipoFK);

	Entity jugador = Entity("Jugador", jugadorColumnas, jugadorFks);

	//puesto
	Column puestoId = Column("puestoId", DataType::INTEGER, true);
	Column puestoNombre = Column("puestoNombre", DataType::VARCHAR, false);

	vector<Column> puestoColumnas;
	puestoColumnas.push_back(puestoId);
	puestoColumnas.push_back(puestoNombre);

	Entity puesto = Entity("Puesto", puestoColumnas);

	//juegadorPuesto
	Column jugadorPuestoId = Column("jugadorPuestoId", DataType::INTEGER, true);
	Column jugadorPuestoJugadorId = Column("jugadorPuestoJugadorId", DataType::INTEGER, false);
	Column jugadorPuestoPuestoId = Column("jugadorPuestoPuestoId", DataType::INTEGER, false);

	vector<Column> jugadorPuestoColumnas;
	jugadorPuestoColumnas.push_back(jugadorPuestoId);
	jugadorPuestoColumnas.push_back(jugadorPuestoJugadorId);
	jugadorPuestoColumnas.push_back(jugadorPuestoPuestoId);

	ForeignKey jugadorPuestoJugadorFK = ForeignKey("Juego", "JugadorPuesto", "id", "jugadorPuestoJugadorId");
	ForeignKey jugadorPuestoPuestoFK = ForeignKey("Puesto", "JugadorPuesto", "id", "jugadorPuestoPuestoId");

	vector<ForeignKey> jugadorPuestoFks;
	jugadorPuestoFks.push_back(jugadorPuestoJugadorFK);
	jugadorPuestoFks.push_back(jugadorPuestoPuestoFK);

	Entity jugadorPuesto = Entity("JugadorPuesto", jugadorPuestoColumnas, jugadorPuestoFks);

	//turno
	Column turnoId = Column("turnoId", DataType::INTEGER, true);
	Column turnoEntradaId = Column("turnoEntradaId", DataType::INTEGER, false);
	
	vector<Column> turnoColumnas;
	turnoColumnas.push_back(turnoId);
	turnoColumnas.push_back(turnoEntradaId);

	Entity turno = Entity("Turno", turnoColumnas);

	//lanzamiento
	Column lanzamientoId = Column("lanzamientoId", DataType::INTEGER, true);
	Column lanzamientoTurnoId = Column("lanzamientoTurnoId", DataType::INTEGER, false);
	Column lanzamientoPitcherId = Column("lanzamientoPitcherId", DataType::INTEGER, false);

	vector<Column> lanzamientoColumnas;
	lanzamientoColumnas.push_back(lanzamientoId);
	lanzamientoColumnas.push_back(lanzamientoTurnoId);
	lanzamientoColumnas.push_back(lanzamientoPitcherId);

	ForeignKey lanzamientoJugadorFk = ForeignKey("Jugador", "Lanzamiento", "id", "lanzamientoPitcherId");

	vector<ForeignKey> lanzamientoFks;
	lanzamientoFks.push_back(lanzamientoJugadorFk);

	Entity lanzamiento = Entity("Lanzamiento", lanzamientoColumnas, lanzamientoFks);

	//carrera
	Column carreraId = Column("carreraId", DataType::INTEGER, true);
	Column carreraJugadorId = Column("carreraJugadorId", DataType::INTEGER, false);
	Column carreraTurnoId = Column("carreraTurnoId", DataType::INTEGER, false);

	vector<Column> carreraColumnas;
	carreraColumnas.push_back(carreraId);
	carreraColumnas.push_back(carreraJugadorId);
	carreraColumnas.push_back(carreraTurnoId);

	ForeignKey carreraJugadorFk = ForeignKey("Jugador", "Carrera", "id", "carreraJugadorId");
	ForeignKey carreraTurnoFk = ForeignKey("Turno", "Carrera", "id", "carreraTurnoId");


	vector<ForeignKey> carreraFks;
	carreraFks.push_back(carreraJugadorFk);
	carreraFks.push_back(carreraTurnoFk);

	Entity carrera = Entity("Carrera", carreraColumnas, carreraFks);

	//tablas
	vector<Entity> entities;
	entities.push_back(estadio);
	entities.push_back(equipo);
	entities.push_back(juego);
	entities.push_back(entrada);
	entities.push_back(jugador);
	entities.push_back(puesto);
	entities.push_back(jugadorPuesto);
	entities.push_back(turno);
	entities.push_back(lanzamiento);
	entities.push_back(carrera);

	dbms.addTable(entities);
}

void printStructDbms() {
	for (unsigned tableIndex = 0; tableIndex < dbms.getTables().size(); tableIndex++) {
		Entity table = dbms.getTables().at(tableIndex);
		vector<Column> columns = table.getColumns();
		vector<ForeignKey> foreingKeys = table.getForeignKeys();
		cout << endl << endl;
		cout << " Tabla : " << table.getName() << endl;

		if (!columns.empty()) {
			cout << " ********** Columns *********** " << endl;
			for (unsigned columnIndex = 0; columnIndex < columns.size(); columnIndex++) {
				Column column = columns.at(columnIndex);

				cout << " >>>> Colum: " << column.getName() << endl;
			}
		}

		if (!foreingKeys.empty()) {
			cout << " ********** ForeingKeys *********** " << endl;
			for (unsigned foreingKeyIndex = 0; foreingKeyIndex < foreingKeys.size(); foreingKeyIndex++) {
				ForeignKey foreingKey = foreingKeys.at(foreingKeyIndex);

				cout << " >>>> ForeingKey: " << foreingKey.getColumnChild() << " <> " << foreingKey.getEntityParent() << "." << foreingKey.getColumnParent() << endl;
			}
		}
	}
}

void inserData() {
	Entity estadio = dbms.getTable("Estadio");
	Entity equipo = dbms.getTable("Equipo");
	Entity juego = dbms.getTable("Juego");
	Entity entrada = dbms.getTable("Entrada");
	Entity jugador = dbms.getTable("Jugador");

	vector<string> estadioData = { "1","Tetelo Varga","01-03-1998"};
	estadio.insertRow(estadioData);

	vector<string> equipoData = {"1","Licey","01-02-1930","20"};
	equipo.insertRow(equipoData);

	equipoData = { "2","Aguilas","01-02-1940","20" };
	equipo.insertRow(equipoData);

	vector<string> juegoData = {"1","1","01-01-2015","1","2"};
	juego.insertRow(juegoData);

	vector<string> entradaData = {"1","Una entrada"};
	entrada.insertRow(entradaData);

	vector<string> jugadorData = { "1","Gabriel","Perez","27","1" };
	jugador.insertRow(jugadorData);

	jugadorData = { "2","Moquete","Perez","25","2" };
	jugador.insertRow(jugadorData);
	
	//print errors.
	//if (player.getErrorMessage().length() > 0)
	//	cout << player.getErrorMessage() << endl;

	//if (position.getErrorMessage().length() > 0)
	//	cout << position.getErrorMessage() << endl;
}

void select() {
	Entity player = dbms.getTable("player");
	Entity position = dbms.getTable("position");

	player.select();
	position.select();
}

void selectCondition() {
	Entity player = dbms.getTable("player");

	vector<string> columns = { "id","name" };
	vector<WhereCondition> whereConditions = {WhereCondition("id","1",Operator::AND )};

	player.select(columns, whereConditions);
}

