import { sequelize } from "../utils/connection.js";
import { DataTypes, Model } from "sequelize";


class Esp extends Model { }

Esp.init({
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
}, {
    modelName: "Esp",
    sequelize,
    tableName: "esps",
    timestamps: false
});

export default Esp;
