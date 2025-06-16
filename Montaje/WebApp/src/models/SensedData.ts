import { sequelize } from "../utils/connection.js";
import { DataTypes, Model } from "sequelize";


class SensedData extends Model { }

SensedData.init({
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
}, {
    modelName: "SensedData",
    sequelize,
    tableName: "sensed_data",
    timestamps: false
});

export default SensedData;
