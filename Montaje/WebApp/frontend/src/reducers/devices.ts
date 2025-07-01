import { newNotification } from "./notification";
import { createOne, deleteOne as deleteOneFromConfig, getFromOneDevice as getFromOneDeviceConfig, updateOne } from "../services/config";
import { getFromOneDevice as getFromOneDeviceData } from "../services/data";
import { deleteOne, getAll } from "../services/devices";
import { GetState } from "../store";
import { Config, ConfigWithId, GenericConfigSchema, configWithIdSchema } from "../types/configs";
import { DataWithId } from "../types/data";
import { DeviceWithId } from "../types/device";
import { Dispatch, UnknownAction, createSlice } from "@reduxjs/toolkit";


const deviceSlice = createSlice({
    initialState: {
        configs: [] as ConfigWithId[],
        data: [] as DataWithId[],
        devices: [] as DeviceWithId[],
        loading: false
    },
    name: "devices",
    reducers: {
        addOne(state, action) {
            return {
                ...state,
                devices: state.devices.concat(action.payload)
            };
        },
        removeOne(state, action) {
            return {
                ...state,
                devices: state.devices.filter((e) => (e.id !== action.payload))
            };
        },
        set(state, action) {
            return {
                ...state,
                devices: action.payload
            };
        },
        setConfigs(state, action) {
            return {
                ...state,
                configs: action.payload as ConfigWithId[]
            };
        },
        setData(state, action) {
            return {
                ...state,
                data: action.payload as DataWithId[]
            };
        },
        setLoading(state, action) {
            return {
                ...state,
                loading: action.payload as boolean
            };
        }
    }
});

export const { set, addOne, removeOne, setLoading, setData, setConfigs } = deviceSlice.actions;

export const loadAllDevices = () => (
    async (dispatch: Dispatch) => {
        try {
            dispatch(setLoading(true));
            const data = await getAll();
            dispatch(setLoading(false));
            dispatch(set(data));
        } catch (error) {
            console.error(error);
            dispatch(set([]));
            dispatch(newNotification({
                message: "Error while loading all devices",
                variant: "danger"
            }));
        }
    }
) as unknown as UnknownAction;

export const removeDevice = (id: number) => (
    async (dispatch: Dispatch) => {
        try {
            dispatch(setLoading(true));
            await deleteOne(id);
            dispatch(setLoading(false));
            dispatch(removeOne(id));
            dispatch(newNotification({
                message: "Device delete successful",
                variant: "success"
            }));
        } catch (error) {
            console.error(error);
            dispatch(newNotification({
                message: "Error while removing device",
                variant: "danger"
            }));
        }
    }
) as unknown as UnknownAction;

export const loadConfigsOfDevice = (id: number) => (
    async (dispatch: Dispatch) => {
        try {
            dispatch(setLoading(true));
            const data = await getFromOneDeviceConfig(id);
            dispatch(setLoading(false));
            dispatch(setConfigs(data));
        } catch (error) {
            console.error(error);
            dispatch(newNotification({
                message: "Error while loading device config",
                variant: "danger"
            }));
        }
    }
) as unknown as UnknownAction;

export const loadDataOfDevice = (id: number) => (
    async (dispatch: Dispatch) => {
        try {
            dispatch(setLoading(true));
            const data = await getFromOneDeviceData(id);
            dispatch(setLoading(false));
            dispatch(setData(data));
        } catch (error) {
            console.error(error);
            dispatch(newNotification({
                message: "Error while loading device data",
                variant: "danger"
            }));
        }
    }
) as unknown as UnknownAction;

export const updateOrCreateConfig = (newConfig: GenericConfigSchema) => (
    async (dispatch: Dispatch, getState: GetState) => {
        try {
            let newConfigs = [];
            if (configWithIdSchema.safeParse(newConfig).success) {
                dispatch(setLoading(true));
                await updateOne(newConfig as ConfigWithId);
                dispatch(setLoading(false));
                dispatch(newNotification({
                    message: "Config updated successfully",
                    variant: "success"
                }));
                newConfigs = getState().devices.configs.map((e) => (e.id !== newConfig.id ? e : newConfig));
            } else {
                dispatch(setLoading(true));
                const createdConfig = await createOne(newConfig as Config);
                dispatch(setLoading(false));
                dispatch(newNotification({
                    message: "Config created successfully",
                    variant: "success"
                }));
                newConfigs = getState().devices.configs.concat(createdConfig);
            }
            dispatch(setConfigs(newConfigs));
        } catch (error) {
            console.error(error);
            dispatch(newNotification({
                message: "Error while update or create of config",
                variant: "danger"
            }));
        }
    }
) as unknown as UnknownAction;

export const deleteConfig = (id: number) => (
    async (dispatch: Dispatch, getState: GetState) => {
        try {
            let configs = getState().devices.configs;
            dispatch(setLoading(true));
            await deleteOneFromConfig(id);
            dispatch(setLoading(false));
            configs = configs.filter((e) => (e.id !== id));
            dispatch(setConfigs(configs));
            dispatch(newNotification({
                message: "Config deleted successfully",
                variant: "success"
            }));
        } catch (error) {
            console.error(error);
            dispatch(newNotification({
                message: "Error while deleting config",
                variant: "danger"
            }));
        }
    }
) as unknown as UnknownAction;

const deviceReducer = deviceSlice.reducer;
export default deviceReducer;
