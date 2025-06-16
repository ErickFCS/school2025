import { POSTGRES_URI } from "./config.js";
import { Sequelize } from "sequelize";
import { SequelizeStorage, Umzug } from "umzug";


export const sequelize = new Sequelize(POSTGRES_URI);

export const runMigrations = async () => {
    const migrator = new Umzug({
        context: sequelize.getQueryInterface(),
        logger: console,
        migrations: {
            glob: "build/src/migrations/*.js"
        },
        storage: new SequelizeStorage({ sequelize, tableName: "migrations" })
    });
    const migration = await migrator.up();
    console.log("Migrations are up to date", {
        files: migration.map((e) => (e.name))
    });
};

export const connectToDatabase = async () => {
    try {
        await sequelize.authenticate();
        await runMigrations();
        console.log("Connection to the database has been established successfully.");
    } catch (error) {
        console.error("Unable to connect to the database:", error);
    }
};
