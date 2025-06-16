import { sequelize } from "../utils/connection.js";
import { DataTypes, Model } from "sequelize";


class Configuration extends Model { }

Configuration.init({
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
}, {
    modelName: "Configuration",
    sequelize,
    tableName: "configurations",
    timestamps: false
});

export default Configuration;
