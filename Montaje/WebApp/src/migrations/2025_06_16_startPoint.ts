import { DataTypes, QueryInterface } from "sequelize";


export const up = async ({ context: queryInterface }: { context: QueryInterface }) => {
    await queryInterface.createTable("esps", {
        id: {
            autoIncrement: true,
            primaryKey: true,
            type: DataTypes.INTEGER
        },
        password: {
            allowNull: false,
            type: DataTypes.STRING
        },
        startTime: {
            type: DataTypes.DATE
        }
    });
    await queryInterface.createTable("configurations", {
        espId: {
            allowNull: true,
            onDelete: "NO ACTION",
            references: {
                key: "id",
                model: "esps"
            },
            type: DataTypes.INTEGER
        },
        field: {
            allowNull: false,
            type: DataTypes.STRING
        },
        groupId: {
            allowNull: true,
            type: DataTypes.INTEGER
        },
        id: {
            autoIncrement: true,
            primaryKey: true,
            type: DataTypes.INTEGER
        },
        value: {
            allowNull: false,
            type: DataTypes.STRING
        }
    });
    await queryInterface.createTable("sensed_data", {
        espId: {
            allowNull: false,
            onDelete: "CASCADE",
            references: {
                key: "id",
                model: "esps"
            },
            type: DataTypes.INTEGER
        },
        id: {
            autoIncrement: true,
            primaryKey: true,
            type: DataTypes.INTEGER
        },
        timestamp: {
            allowNull: false,
            type: DataTypes.DATE
        },
        type: {
            allowNull: false,
            type: DataTypes.STRING
        },
        value: {
            allowNull: false,
            type: DataTypes.STRING
        }
    });
    await queryInterface.createTable("users", {
        id: {
            autoIncrement: true,
            primaryKey: true,
            type: DataTypes.INTEGER
        },
        password: {
            allowNull: false,
            type: DataTypes.STRING
        },
        username: {
            allowNull: false,
            type: DataTypes.STRING,
            unique: true
        }
    });
};

export const down = async ({ context: queryInterface }: { context: QueryInterface }) => {
    await queryInterface.dropTable("users");
    await queryInterface.dropTable("sensed_data");
    await queryInterface.dropTable("configurations");
    await queryInterface.dropTable("esps");
};
